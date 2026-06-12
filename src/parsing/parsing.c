/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:10:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/06/03 21:29:09 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	parsing(t_shell	*shell)
{
	if (lexing(&shell->tokens, shell->lineread, &shell->exit_code) != 0)
		return (1);
	set_types(shell->tokens);
	set_commands(shell->tokens);
	if (expansion(&shell->tokens, shell) != 0)
		return (shell->exit_code = 1, 1);
	if (!shell->tokens || (shell->tokens && !shell->tokens->next
			&& shell->tokens->content[0] == '\0'))
		return (1);
	set_types(shell->tokens);
	set_commands(shell->tokens);
	if (syntax_check(shell) != 0)
		return (shell->exit_code = 2, 1);
	if (handle_heredoc_tokens(shell, shell->tokens) != 0)
		return (1);
	return (0);
}

void	set_types(t_token *tlist)
{
	t_token	*temp;

	temp = tlist;
	while (temp)
	{
		if (ft_strcmp(temp->content, "<<") == 0 && !temp->has_quotes)
			temp->type = HEREDOC;
		else if (ft_strcmp(temp->content, ">>") == 0 && !temp->has_quotes)
			temp->type = APPEND;
		else if (ft_strcmp(temp->content, "<") == 0 && !temp->has_quotes)
			temp->type = INFILE;
		else if (ft_strcmp(temp->content, ">") == 0 && !temp->has_quotes)
			temp->type = OUTFILE;
		else if (ft_strcmp(temp->content, "|") == 0 && !temp->has_quotes)
			temp->type = PIPE;
		else if (temp->prev && temp->prev->type == HEREDOC)
			temp->type = LIMITER;
		else if (temp->prev && (temp->prev->type == INFILE
				|| temp->prev->type == OUTFILE || temp->prev->type == APPEND))
			temp->type = TFILE;
		temp = temp->next;
	}
}

void	set_commands(t_token *tlist)
{
	t_token	*temp;
	int		check;

	temp = tlist;
	check = 0;
	while (temp)
	{
		if (check == 0 && (temp->type == ARG || temp->type == COMMAND))
		{
			temp->type = COMMAND;
			check = 1;
		}
		else if (temp->type == PIPE)
			check = 0;
		temp = temp->next;
	}
}
