/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 01:38:51 by manmaria          #+#    #+#             */
/*   Updated: 2026/04/29 01:39:04 by manmaria         ###   ########.fr       */
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

t_cmd	*create_builtin(t_token **token, t_cmd *bi)
{
	t_token	*temp;
	int		i;

	temp = *token;
	bi->path = (*token)->content;
	while (temp->type == ARG)
	{
		bi->arg_count++;
		temp = temp->next;
	}
	i = 0;
	if (bi->arg_count > 0)
	{
		temp = (*token)->next->next;
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


t_cmd	*create_command(t_token **token, t_env *env)
{
	t_cmd	*cmd;
	
	cmd = NULL;
	if ((*token)->type == COMMAND)
	{
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		if (is_builtin(*token))
			cmd = create_builtin(token, cmd);
		else
			cmd = create_external(token, env);
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
		command = create_command(&token, envs);
		if (!command)
			return (cmdlist_clear(&cmds));
	}
	return (cmds);
}
