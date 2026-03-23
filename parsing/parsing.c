/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:10:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/23 18:08:28 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	parsing(t_shell	*shell)
{
	int err_code;

	err_code = 0;
	shell->tokens = lexing(shell->lineread, &err_code);
	set_types(shell->tokens);
	set_commands(shell->tokens);
	if (!expansion(shell->tokens, shell))
	{
		// TODO: refactor LIST_CLEAR()
		// return(dlist_list_clear(&shell->tokens, free_token_data), 0);
		printf("%s 4 \n", shell->lineread);
	}
	return (1);
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
		else if (temp->prev && (temp->prev->type == INFILE || temp->prev->type == OUTFILE
				|| temp->prev->type == APPEND))
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
		if (check == 0 && temp->type == ARG)
		{
			temp->type = COMMAND;
			check = 1;
		}
		else if (temp->type == PIPE)
			check = 0;
		temp = temp->next;
	}
}
