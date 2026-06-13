/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 18:43:22 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/13 20:31:29 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

int	exec_builtin(t_shell *sh, t_cmd *cmd, bool in_child)
{
	int	status;

	status = 0;
	if (cmd->redirect_count > 0 && !in_child && apply_redirects(cmd) < 0)
		status = 1;
	else
	{
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
	}
	if (in_child == true)
		cleanup_and_exit(status, sh, cmd);
	return (status);
}

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

void	execve_error(t_shell *shl, t_cmd *command, char	*path)
{
	struct stat	stt;

	ft_printf_fd(2, SH_ "%s: ", command->args[0]);
	if (errno == EACCES && stat(path, &stt) == 0 && S_ISDIR(stt.st_mode))
	{
		ft_printf_fd(2, ERR_DIREC);
		cleanup_and_exit(126, shl, command);
	}
	if (!ft_strchr(command->path, '/') && errno != EACCES)
	{
		ft_printf_fd(2, ERR_CMD);
		cleanup_and_exit(127, shl, command);
	}
	ft_printf_fd(2, "%s\n", strerror(errno));
	if (errno == EACCES)
		cleanup_and_exit(126, shl, command);
	if (errno == ENOENT)
		cleanup_and_exit(127, shl, command);
	cleanup_and_exit(1, shl, command);
	exit(1);
}
