/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:39:23 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/11 17:02:54 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOTE:
//	   executor(t_shell *sh)
//	   ├─ build_command_list(sh->tokens, sh->envs)
//	   │  └─ Creates: t_cmd linked list
//	   │     └─ Each t_cmd has: path, args, arg_count, is_bi flag
//	   ├─ exec_pipeline(sh, cmdlist)
//	   │  ├─ command_count(cmds) → returns N
//	   │  ├─ if N == 1 && is_builtin → exec_builtin(sh, cmds) [NO FORK]
//	   │  ├─ else → iterative pipeline:
//	   │  │  ├─ Initialize: count=0, prev_read=-1, pids[1024]
//	   │  │  ├─ For each command:
//	   │  │  │  ├─ if (not last) → pipe(pipefd) creates read/write fds
//	   │  │  │  ├─ fork() → pid
//	   │  │  │  ├─ if (pid == 0) → CHILD:
//	   │  │  │  │  ├─ dup2(prev_read, STDIN) [if not first]
//	   │  │  │  │  ├─ dup2(pipefd[1], STDOUT) [if not last]
//	   │  │  │  │  ├─ close all pipe fds
//	   │  │  │  │  ├─ if is_builtin → exec_builtin(sh, cmd)
//	   │  │  │  │  └─ else → execve(cmd->path, cmd->args, envp)
//	   │  │  │  │     └─ exit(status)
//	   │  │  │  └─ else → PARENT:
//	   │  │  │     ├─ pids[count++] = pid
//	   │  │  │     ├─ close(prev_read) [if not first]
//	   │  │  │     ├─ if (not last):
//	   │  │  │     │  ├─ close(pipefd[1])
//	   │  │  │     │  └─ prev_read = pipefd[0]
//	   │  │  │     └─ else: prev_read = -1
//	   │  │  └─ For each pid: waitpid(pids[i], &status, 0)
//	   │  │     └─ if (last child) → sh->exit_code = WEXITSTATUS(status)
//	   │  └─ return sh->exit_code
//	   ├─ cmdlist_clear(&cmdlist)
//	   └─ return status

#include "../../incs/executor.h"
#include "../../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

static void	exec_pipeline_child(t_shell *sh, t_cmd *curr, int *pipefd)
{
	char	**envp;

	if (sh->pipeline.prev_read != -1)
	{
		if (dup2(sh->pipeline.prev_read, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(sh->pipeline.prev_read);
	}
	if (curr->next)
	{
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
	}
	if (curr->redirect_count > 0 && apply_redirects(curr) < 0)
		cleanup_and_exit(1, sh, curr);
	if (curr->is_bi)
		exec_builtin(sh, curr, true);
	envp = env_list_to_array(sh->envs);
	if (!envp)
		return(ft_printf_fd(2, SH_ERR ERR_MALLOC), cleanup_and_exit(1, sh, curr));
	execve(curr->path, curr->args, envp);
	free_split(envp);
	execve_error(sh, curr, curr->path);
	exit(127);
}

static void	exec_pipeline_parent(t_shell *sh, t_cmd *curr, int *pipefd,
	pid_t pid)
{
	sh->pipeline.pids[sh->pipeline.count++] = pid;
	if (sh->pipeline.prev_read != -1)
		close(sh->pipeline.prev_read);
	if (curr->next)
	{
		close(pipefd[WRITE_END]);
		sh->pipeline.prev_read = pipefd[READ_END];
	}
	else
		sh->pipeline.prev_read = -1;
}

static void	wait_for_children(t_shell *sh)
{
	int		status;
	int		i;

	i = 0;

	block_signals();
	while (i < sh->pipeline.count)
	{
		waitpid(sh->pipeline.pids[i], &status, 0);
		if (i == sh->pipeline.count - 1)
		{
			if (WIFEXITED(status))
				sh->exit_code = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				sh->exit_code = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	handle_signal();
}

int	exec_pipeline(t_shell *sh, t_cmd *cmds)
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	*curr;

	if (!cmds)
		return (1);// WARNING: error code?
	if (!cmds->next && cmds->is_bi)
	{
		save_parent_fds(sh, true);
		int status = exec_builtin(sh, cmds, false);
		restore_fds(sh);
		return (status);
	}
	if (!cmds->next && cmds->is_bi)
		return (exec_builtin(sh, cmds, false));
	init_pipeline(sh);
	curr = cmds;
	while (curr && sh->pipeline.count < 1024)
	{
		handle_signal();
		pid = setup_pipes_and_fork(sh, curr, pipefd);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (curr->next)
				close(pipefd[READ_END]);
			handle_signal_child();
			exec_pipeline_child(sh, curr, pipefd);
		}
		else
			exec_pipeline_parent(sh, curr, pipefd, pid);
		curr = curr->next;
	}
	wait_for_children(sh);
	return (sh->exit_code);
}//NOTE: idk what to do with this sh->exit_code return below

int	executor(t_shell *sh)
{
	t_cmd	*cmdlist;
	int		status;

	status = 0;
	cmdlist = build_command_list(sh->tokens, sh->envs, &status);
	if (status == 1)
		return (sh->exit_code = 1, 1);
	status = exec_pipeline(sh, cmdlist);
	cmdlist_clear(&cmdlist);
	sh->exit_code = status; //NOTE: in case exec_pip returns 1 ?
	return (status);
}
