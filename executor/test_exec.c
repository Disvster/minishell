/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disaster </var/spool/mail/disaster>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:32:08 by disaster          #+#    #+#             */
/*   Updated: 2026/05/12 23:33:03 by disaster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"
#include "../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

static int	command_count(t_cmd *head)
{
	int		count;
	t_cmd	*temp;

	count = 0;
	temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static char	**env_list_to_array(t_env *envs)
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
	int	status;

	// Redirect stdin from previous pipe
	if (sh->pipeline.prev_read != -1)
	{
		if (dup2(sh->pipeline.prev_read, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(sh->pipeline.prev_read);
	}
	
	// Redirect stdout to current pipe (if not last command)
	if (curr->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
	
	sh->pipeline.prev_read = -1;
	sh->pipeline.count = 0;
	
	// Execute command
	if (curr->is_bi)
		status = exec_builtin(sh, curr);
	else
	{
		char **envp = env_list_to_array(sh->envs);
		if (!envp)
			exit(1);
		execve(curr->path, curr->args, envp);
		perror("execve");
		free_split(envp);
		exit(127);
	}
	exit(status);
}

static void	exec_pipeline_parent(t_shell *sh, t_cmd *curr, int *pipefd, pid_t pid)
{
	// Store child PID
	sh->pipeline.pids[sh->pipeline.count++] = pid;
	
	// Close previous pipe's read end (child is using it)
	if (sh->pipeline.prev_read != -1)
		close(sh->pipeline.prev_read);
	
	// Save current pipe's read end for next iteration
	if (curr->next)
	{
		close(pipefd[1]);
		sh->pipeline.prev_read = pipefd[0];
	}
	else
		sh->pipeline.prev_read = -1;
}

int	exec_pipeline(t_shell *sh, t_cmd *cmds)
{
	int		cmd_count;
	int		pipefd[2];
	pid_t	pid;
	t_cmd	*curr;
	int		i;
	int		status;

	cmd_count = command_count(cmds);
	if (cmd_count == 0)
		return (0);
	
	// Single built-in optimization (no fork needed)
	if (cmd_count == 1 && cmds->is_bi)
		return (exec_builtin(sh, cmds));
	
	// Initialize pipeline state
	sh->pipeline.count = 0;
	sh->pipeline.prev_read = -1;
	ft_memset(sh->pipeline.pids, -1, 1024 * sizeof(pid_t));
	
	// Main pipeline loop
	curr = cmds;
	while (curr && sh->pipeline.count < 1024)
	{
		// Create pipe if not the last command
		if (curr->next)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				if (sh->pipeline.prev_read != -1)
					close(sh->pipeline.prev_read);
				return (1);
			}
		}
		
		// Fork child process
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
			return (1);
		}
		
		if (pid == 0)
		{
			// Child process
			if (curr->next)
			{
				close(pipefd[0]);
				exec_pipeline_child(sh, curr, pipefd);
			}
			else
				exec_pipeline_child(sh, curr, NULL);
		}
		else
		{
			// Parent process
			exec_pipeline_parent(sh, curr, pipefd, pid);
		}
		
		curr = curr->next;
	}
	
	// Wait for all children
	i = 0;
	while (i < sh->pipeline.count)
	{
		waitpid(sh->pipeline.pids[i], &status, 0);
		if (i == sh->pipeline.count - 1)
			sh->exit_code = WEXITSTATUS(status);
		i++;
	}
	
	return (sh->exit_code);
}

int	executor(t_shell *sh)
{
	t_cmd	*cmdlist;
	int		status;

	if (!sh || !sh->tokens)
		return (1);
	
	// Build command list from tokens
	cmdlist = build_command_list(sh->tokens, sh->envs);
	if (!cmdlist)
		return (1);
	
	// Execute pipeline
	status = exec_pipeline(sh, cmdlist);
	
	// Cleanup
	cmdlist_clear(&cmdlist);
	
	return (status);
}
