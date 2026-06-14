/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:21:54 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/11 17:06:23 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/executor.h"
#include "../../../incs/minishell.h"

int	is_builtin(t_token *token)
{
	if (!ft_strcmp(token->content, "echo")
		|| !ft_strcmp(token->content, "env")
		|| !ft_strcmp(token->content, "pwd")
		|| !ft_strcmp(token->content, "exit")
		|| !ft_strcmp(token->content, "cd")
		|| !ft_strcmp(token->content, "export")
		|| !ft_strcmp(token->content, "unset"))
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

int	search_paths(char **paths, char *cmd, char	**test)
{
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (*test = ft_strdup(cmd), 0);
		return (*test = ft_strdup(cmd), 127);
	}
	i = -1;
	if (paths)
	{
		while (paths[++i])
		{
			*test = pipex_strjoin(paths[i], cmd);
			if (!*test)
				return (1);
			if (access(*test, X_OK) == 0)
				return (0);
			free(*test);
			*test = NULL;
		}
	}
	return (*test = ft_strdup(cmd), 127);
}

int	find_cmd_path(t_cmd	*ext, char *cmd, t_env *envlist)
{
	int		status;
	char	**paths;
	char	*test;

	status = 0;
	paths = NULL;
	test = NULL;
	while (envlist && ft_strncmp("PATH", envlist->name, 4))
		envlist = envlist->next;
	if (envlist)
	{
		paths = ft_split(envlist->content, ':');
		if (!paths)
			return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
	}
	status = search_paths(paths, cmd, &test);
	free_split(paths);
	if (!test && cmd)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
	ext->path = test;
	return (status);
}

int	token_is_redir(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	redir_only_cmd_node(t_token **token, t_cmd **cmd)
{
	t_cmd	*node;

	node = ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
	node->is_bi = true;
	*cmd = node;
	if ((*token)->next)
		*token = (*token)->next;
	return (0);
}

int	tokenlist_has_commands(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
