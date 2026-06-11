/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 01:38:51 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/11 17:02:54 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/executor.h"
#include "../../../incs/minishell.h"

void	populate_args(t_token *token, t_cmd *cmd, bool is_bi)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (is_bi == false)
		i++;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			cmd->args[i++] = tmp->content;
		tmp = tmp->next;
	}
}

int	create_external(t_token *token, t_cmd *ext, t_env *envlist)
{
	t_token	*temp;
	int	status;

	status = 0;
	status = find_cmd_path(ext, token->content, envlist);
	if (status == 1)
		return (status);
	temp = token->next;
	while (temp && (temp->type != PIPE && temp->type != COMMAND))
	{
		if (temp->type == ARG)
			ext->arg_count++;
		temp = temp->next;
	}
	ext->args = ft_calloc((ext->arg_count + 2), sizeof(char *));
	if (!ext->args)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
	ext->args[0] = token->content;
	if (ext->arg_count > 0)
	{
		temp = token->next;
		populate_args(temp, ext, false);
	}
	return (status);
}

int	create_builtin(t_token *token, t_cmd *bi)
{
	t_token	*temp;

	bi->path = token->content;
	temp = token->next;
	bi->is_bi = true;
	while (temp && (temp->type != PIPE && temp->type != COMMAND))
	{
		if (temp->type == ARG)
			bi->arg_count++;
		temp = temp->next;
	}
	if (bi->arg_count > 0)
	{
		temp = token->next;
		bi->args = ft_calloc((bi->arg_count + 1), sizeof(char *));
		if (!bi->args)
			return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
		populate_args(temp, bi, true);
	}
	return (0);
}

int	create_command(t_cmd **command, t_token **token, t_env *envlist)
{
	t_cmd	*cmd;
	int		i;
	int		status;

	cmd = NULL;
	status = 0;
	if ((*token)->type == COMMAND)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (ft_printf_fd(2, SH_ERR ERR_MALLOC), 1);
		if (is_builtin(*token))
			status = create_builtin(*token, cmd);
		else
			status = create_external(*token, cmd, envlist);
	}
	if (cmd && status != 1)
	{
		populate_redirects(*token, cmd);
		i = -1;
		while (*token && ++i < cmd->arg_count)
			*token = (*token)->next;
	}
	*command = cmd;
	return (status);
}

t_cmd	*build_command_list(t_token *head, t_env *envs, int *status)
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
		if (token->type == COMMAND)
		{
			*status = create_command(&command, &token, envs);
			if (*status == 1)
				return (cmdlist_clear(&cmds));
			cmdlist_add_last(&cmds, command);
		}
		if (!token)
			break ;
		token = token->next;
	}
	return (cmds);
}
// NOTE: cmdlist_clear cleans list and returns NULL
// and the function that calls build_command_list() 
// takes care of the cleanup and error management
// if (token->next)
