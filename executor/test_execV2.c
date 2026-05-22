/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execV2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:39:23 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 18:15:39 by manmaria         ###   ########.fr       */
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

#include "../incs/executor.h"
#include "../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		return (exec_echo(sh, cmd));
	else if (ft_strcmp(cmd->path, "env") == 0)
		return (exec_env(sh));
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		return (exec_pwd(sh));
	else if (ft_strcmp(cmd->path, "exit") == 0)
		return (exec_exit(sh, cmd));
	else if (ft_strcmp(cmd->path, "export") == 0)
		return (exec_export(sh, cmd));
	else if (ft_strcmp(cmd->path, "unset") == 0)
		return (exec_unset(sh, cmd));
	return (1);
}

// static int	command_count(t_cmd *head)
// {
// 	int		count;
// 	t_cmd	*temp;
//
// 	count = 0;
// 	temp = head;
// 	while (temp)
// 	{
// 		count++;
// 		temp = temp->next;
// 	}
// 	return (count);
// }

char	**env_list_to_array(t_env *envs)
{
	char	**envp;
	int		count;
	int		i;
	t_env	*tmp;
	char	*temp;

	count = envlist_size(envs);
	envp = ft_calloc(count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = envs;
	while (tmp && i < count)
	{
		temp = ft_strjoin(tmp->name, "=");
		if (!temp)
			return (free_split(envp), NULL);
		envp[i] = ft_strjoin(temp, tmp->content);
		free(temp);
		if (!envp[i])
			return (free_split(envp), NULL);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

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
	sh->pipeline.prev_read = -1;
	// sh->pipeline.count = 0;
	if (curr->is_bi)
		exit(exec_builtin(sh, curr));
	envp = env_list_to_array(sh->envs);
	if (!envp)
		exit(1);//WARNING: can I exit here?
	execve(curr->path, curr->args, envp);
	perror("execve");
	free_split(envp);
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

static int	setup_pipes_and_fork(t_shell *sh, t_cmd *curr, int *pipefd)
{
	pid_t	pid;

	if (curr->next)//if (not on last cmd)
	{
		if (pipe(pipefd) < 0)//creates read/write fds
		{
			perror("pipe");
			if (sh->pipeline.prev_read != -1)//If(not on last command)
				close(sh->pipeline.prev_read);//close(write fd of cmd before)
			return (-1);// WARNING: exit code?
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (curr->next)
		{
			close(pipefd[0]);
			close(pipefd[1]);
		}
		if (sh->pipeline.prev_read != -1)
			close(sh->pipeline.prev_read);
		return (-1);
	}
	return (pid);
}

static int	init_pipeline(t_shell *sh)
{
	sh->pipeline.count = 0;
	sh->pipeline.prev_read = -1;
	ft_memset(sh->pipeline.pids, -1, 1024 * sizeof(pid_t));
	return (0);
}

static void	wait_for_children(t_shell *sh)
{
	int		status;
	int		i;

	i = 0;
	while (i < sh->pipeline.count)
	{
		waitpid(sh->pipeline.pids[i], &status, 0);
		if (i == sh->pipeline.count - 1)
			sh->exit_code = WEXITSTATUS(status);
		i++;
	}
}

int	exec_pipeline(t_shell *sh, t_cmd *cmds)
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	*curr;

	if (!cmds)
		return (0);// WARNING: error code?
	if (!cmds->next && cmds->is_bi)
		return (exec_builtin(sh, cmds));
	init_pipeline(sh);
	curr = cmds;
	while (curr && sh->pipeline.count < 1024)
	{
		pid = setup_pipes_and_fork(sh, curr, pipefd);
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (curr->next)//we close READ_END because it is saved in
				close(pipefd[READ_END]);//pipeline.prev_read_end, we don't need it
			exec_pipeline_child(sh, curr, pipefd);
		}
		else
			exec_pipeline_parent(sh, curr, pipefd, pid);
		curr = curr->next;
	}
	wait_for_children(sh);
	return (sh->exit_code);
}

int	executor(t_shell *sh)
{
	t_cmd	*cmdlist;
	int		status;

	if (!sh || !sh->tokens)
		return (1);// WARNING: error code?
	cmdlist = build_command_list(sh->tokens, sh->envs);
	if (!cmdlist)
		return (1);// WARNING: error code?
	status = exec_pipeline(sh, cmdlist);
	cmdlist_clear(&cmdlist);
	return (status);
}
