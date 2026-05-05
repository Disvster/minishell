/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:21:54 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/05 17:29:57 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"
#include "../incs/minishell.h"

int	is_builtin(t_token *token)
{
	if (!(ft_strcmp(token->content, "echo")
			|| ft_strcmp(token->content, "env")
			|| ft_strcmp(token->content, "pwd")
			|| ft_strcmp(token->content, "exit")
			|| ft_strcmp(token->content, "cd")
			|| ft_strcmp(token->content, "export")
			|| ft_strcmp(token->content, "unset")))
		return (1);
	return (0);
}

char	*pipex_strjoin(char *path, char *cmd)
{
	char	*new_cmd;
	size_t	len;
	size_t	path_len;

	path_len = ft_strlen(path);
	len = path_len + ft_strlen(cmd) + 2;
	new_cmd = ft_calloc(len, sizeof(char));
	if (!new_cmd)
		return (NULL);
	ft_strlcpy(new_cmd, path, len);
	new_cmd[path_len] = '/';
	ft_strlcpy(new_cmd + path_len + 1, cmd, len - path_len - 1);
	return (new_cmd);
}

char	*search_paths(char **paths, char *cmd)
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

char	*find_cmd_path(char *cmd, t_env *envlist)
{
	char	**paths;
	char	*test;

	// NOTE: do I need to create a temp for envlist?
	while (envlist && ft_strncmp("PATH=", envlist->content, 5))
		envlist = envlist->next;
	if (!envlist)
		return (NULL);
	paths = ft_split(envlist->content, ':');
	if (!paths)
		return (NULL);
	test = search_paths(paths, cmd);
	if (!test)
		return (free_split(paths), NULL);
	return (free_split(paths), test);
}

