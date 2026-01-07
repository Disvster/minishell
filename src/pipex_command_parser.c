/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_command_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:01:53 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/07 19:03:50 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	create_args(t_cmd *cmd, char **split_cmd, int wc);

int	get_command(char *cmd_str, char **envp, t_cmd *cmd)
{
	int		wc;
	char	**split_cmd;

	wc = count_words(cmd_str, ' ');
	split_cmd = ft_split(cmd_str, ' ');
	if (!split_cmd)
		return (-1);
	if (wc)
		cmd->path = find_cmd_path(split_cmd[0], envp);
	if (!cmd->path)
		return (free_split(split_cmd), -1);
	if (create_args(cmd, split_cmd, wc) == -1)
		return (free_split(split_cmd), free(cmd->path), -1);
	free_split(split_cmd);
	return (1);
}

static int	create_args(t_cmd *cmd, char **split_cmd, int wc)
{
	int	i;

	cmd->args = ft_calloc(wc + 1, sizeof(char *));
	if (!cmd->args)
		return (-1);
	i = 0;
	while (i < wc && split_cmd[i])
	{
		cmd->args[i] = ft_strdup(split_cmd[i]);
		if (!cmd->args[i])
		{
			while (--i >= 0)
				free(cmd->args[i]);
			free(cmd->args);
			return (-1);
		}
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}

static char	*search_paths(char **paths, char *cmd)
{
	char	*test;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = -1;
	test = NULL;
	while (paths[++i])
	{
		test = pipex_strjoin(paths[i], cmd);
		if (!test)
			return (NULL);
		if (access(test, X_OK) == 0)
			break ;
		free(test);
		test = NULL;
	}
	return (test);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*test;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp, ':');
	if (!paths)
		return (NULL);
	if (ft_strncmp(paths[0], "PATH=", 5) == 0)
		ft_memmove(paths[0], paths[0] + 5, ft_strlen(paths[0] + 5) + 1);
	test = search_paths(paths, cmd);
	if (!test)
		return (free_split(paths), NULL);
	return (free_split(paths), test);
}
