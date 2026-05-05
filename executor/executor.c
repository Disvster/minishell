/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 01:38:51 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/05 19:31:05 by disaster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"
#include "../incs/minishell.h"

void	populate_args(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (token)
	{
			if (token->type == ARG)
				cmd->args[i++] = token->content;// NOTE: where is ownership? here or in token_list?
			if (token->type == INFILE || token->type == OUTFILE
				|| token->type == APPEND || token->type == HEREDOC)
				cmd->redirect_count++;
			token = token->next;
	}
}

t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist)
{
	t_token	*temp;
	int		i;

	ext->path = find_cmd_path(token->content, envlist);
	if (!ext->path)
		return (NULL);
	temp = token->next;
	while (temp && temp->type != PIPE && temp->type != COMMAND)// WARNING: is this enough? should it be more precise?
	{
		ext->arg_count++;
		temp = temp->next;
	}
	i = 0;
	if (ext->arg_count > 0)
	{
		temp = token->next;
		ext->args = ft_calloc((ext->arg_count + 1), sizeof(char *));
		if (!ext->args)
			return (NULL);
		populate_args(temp, ext);
	}
	return (ext);
}

t_cmd	*create_builtin(t_token *token, t_cmd *bi)
{
	t_token	*temp;
	int		i;

	bi->path = token->content;
	temp = token->next;
	while (temp && temp->type != PIPE && temp->type != COMMAND) // WARNING: is this enough? should it be more precise?
	{
		bi->arg_count++;
		temp = temp->next;
	}
	i = 0;
	if (bi->arg_count > 0)
	{
		temp = token->next;
		bi->args = ft_calloc((bi->arg_count + 1), sizeof(char *));
		if (!bi->args)
			return (NULL);
		populate_args(temp, bi);
	}
	bi->is_bi = true;
	return (bi);
}

t_cmd	*create_command(t_token *token, t_env *envlist)
{
	t_cmd	*cmd;
	
	cmd = NULL;
	if (token->type == COMMAND)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		if (is_builtin(token))
			cmd = create_builtin(token, cmd);
		else
			cmd = create_external(token, cmd, envlist);
		cmd->next = NULL;
		cmd->prev = NULL;
	}
	return (cmd);
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
		command = create_command(token, envs);
		if (!command)
			return (cmdlist_clear(&cmds));
		cmdlist_add_last(&cmds, command);
		// NOTE: cmdlist_clear cleans list and returns NULL
		//and the function that calls build_command_list() takes care of the cleanup and error management
	}
	return (cmds);
}
