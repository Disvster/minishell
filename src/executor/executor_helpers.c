/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:08:06 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/06 15:11:01 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

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
	return (envp);
}

int	setup_pipes_and_fork(t_shell *sh, t_cmd *curr, int *pipefd)
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

int	init_pipeline(t_shell *sh)
{
	sh->pipeline.count = 0;
	sh->pipeline.prev_read = -1;
	ft_memset(sh->pipeline.pids, -1, 1024 * sizeof(pid_t));
	return (0);
}

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->redirect_count > 0 && apply_redirects(cmd) < 0)
		return (-1);// FIX: FREE HERE?
	if (ft_strcmp(cmd->path, "cd") == 0)
		status = exec_cd(sh, cmd);
	else if (ft_strcmp(cmd->path, "echo") == 0)
		status = exec_echo(sh, cmd);
	else if (ft_strcmp(cmd->path, "env") == 0)
		status = exec_env(sh);
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		status = exec_pwd(sh);
	else if (ft_strcmp(cmd->path, "exit") == 0)
		status = exec_exit(sh, cmd);
	else if (ft_strcmp(cmd->path, "export") == 0)
		status = exec_export(sh, cmd);
	else if (ft_strcmp(cmd->path, "unset") == 0)
		status = exec_unset(sh, cmd);
	return (status);
}
