/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 01:38:51 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/22 20:25:01 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"

void	populate_args(t_token *token, t_cmd *cmd, bool is_bi)
{
	t_token *tmp;
	int		i;

	i = 0;
	tmp = token;
	if (is_bi == false)
		i++;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			cmd->args[i++] = tmp->content;// NOTE: where is ownership? here or in temp_list?
		tmp = tmp->next;
	}
}


t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist)
{
	t_token	*temp;

	ext->path = find_cmd_path(token->content, envlist);
	if (!ext->path)
		return (free(ext), ft_printf_fd(2, "Error: %s: command not found\n", token->content), NULL);
	temp = token->next;
	while (temp && temp->type == ARG)
	{
		ext->arg_count++;
		temp = temp->next;
	}
	ext->args = ft_calloc((ext->arg_count + 2), sizeof(char *));
	if (!ext->args)
		return (NULL);
	ext->args[0] = token->content;// NOTE: OR ext->path;
	if (ext->arg_count > 0)
	{
		temp = token->next;
		populate_args(temp, ext, false);
	}
	return (ext);
}

t_cmd	*create_builtin(t_token *token, t_cmd *bi)
{
	t_token	*temp;

	bi->path = token->content;
	temp = token->next;
	bi->is_bi = true;
	while (temp && temp->type == ARG)
	{
		bi->arg_count++;
		temp = temp->next;
	}
	if (bi->arg_count > 0)
	{
		temp = token->next;
		bi->args = ft_calloc((bi->arg_count + 1), sizeof(char *));
		if (!bi->args)
			return (NULL);
		populate_args(temp, bi, true);
	}
	return (bi);
}

t_cmd	*create_command(t_token **token, t_env *envlist)
{
	t_cmd	*cmd;
	int		i;

	cmd = NULL;
	if ((*token)->type == COMMAND)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		if (is_builtin(*token))
			cmd = create_builtin(*token, cmd);
		else
			cmd = create_external(*token, cmd, envlist);
	}
	if (cmd)
	{
		populate_redirects(*token, cmd);
		// cmd->next = NULL;
		// cmd->prev = NULL;
		i = -1;//add on more skp here?
		while (*token && ++i < cmd->arg_count)//NOTE: && *token->type != COMMAND
			*token = (*token)->next;
	}
	return (cmd);
}

static int	tokenlist_has_commands(t_token *token)
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

t_cmd	*build_command_list(t_token *head, t_env *envs)
{
	t_token	*token;
	t_cmd	*cmds;
	t_cmd	*command;

	if (!head)
		return (NULL);
	token = head;
	cmds = NULL;
	command = NULL;
	while (token)
	{
		if (token->type == COMMAND)// TODO: && REDIRS
		{
			command = create_command(&token, envs);
			if (!command && tokenlist_has_commands(token))
				return (cmdlist_clear(&cmds));
			cmdlist_add_last(&cmds, command);
		}
		if (!token)// && token->next)//NOTE: do I need this?
			break ;
		token = token->next;
	}
	return (cmds);
}
// NOTE: cmdlist_clear cleans list and returns NULL
// and the function that calls build_command_list() takes care of the cleanup and error management
// if (token->next)
