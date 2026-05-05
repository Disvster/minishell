/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 01:38:51 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/05 17:29:57 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"
#include "../incs/minishell.h"

t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist)
{
	t_token	*temp;
	int		i;

	ext->path = find_cmd_path(token->content, envlist);
	if (!ext->path)
		return (NULL);
	temp = token->next;//
	while (temp && temp->type != PIPE && temp->type != COMMAND)// WARNING: is this enough? should it be more precise?
	{
		ext->arg_count++;
		temp = temp->next;
	}
	i = 0;
	if (ext->arg_count > 0)
	{
		temp = token->next;
		ext->arg_count = ;
		// same as build_builtin? make this into a single helper func for both?
	}
	
	
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
	}
	return (cmd);
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
		while (temp)
		{
			if (temp->type == ARG)
				bi->args[i++] = temp->content;// NOTE: where is ownership? here or in token_list?
			if (temp->type == INFILE || temp->type == OUTFILE
				|| temp->type == APPEND || temp->type == HEREDOC)
				bi->redirect_count++;
			temp = temp->next;
		}
	}
	return (bi);
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
		// TODO: cmdlist_clear cleans list, returns NULL, and the function that calls build_command_list() takes care of the rest of the cleanup and error management
	}
	return (cmds);
}
