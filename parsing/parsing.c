/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:10:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/05 18:00:54 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	parsing(t_shell	*shell)
{
	shell->tokens = lexing(shell->lineread);
	return (1);
}

void	set_types(t_dlist *tlist)
{
	t_dlist	*temp;
	int		len;

	len = 0;
	temp = tlist;
	while (temp)
	{
		len = ft_strlen(temp->data->content);
		if (ft_strncmp(temp->data->content, "<<", len) == 0 && !temp->data->has_quotes)
			temp->data->type = HEREDOC;
		else if (ft_strncmp(temp->data->content, ">>", len) == 0 && !temp->data->has_quotes)
			temp->data->type = APPEND;
		else if (ft_strncmp(temp->data->content, "<", len) == 0 && !temp->data->has_quotes)
			temp->data->type = INFILE;
		else if (ft_strncmp(temp->data->content, ">", len) == 0 && !temp->data->has_quotes)
			temp->data->type = OUTFILE;
		else if (ft_strncmp(temp->data->content, "|", len) == 0 && !temp->data->has_quotes)
			temp->data->type = PIPE;
		else if (temp->prev && temp->prev->data->type == HEREDOC)
			temp->data->type = LIMITER;
		else if (temp->prev && (temp->prev->data->type == INFILE || temp->prev->data->type == OUTFILE
				|| temp->prev->data->type == APPEND))
			temp->data->type = TFILE;
		temp = temp->next;
	}
}

void	set_commands(t_dlist *tlist)
{
	t_dlist	*temp;
	int		check;

	temp = tlist;
	check = 0;
	while (temp)
	{
		if (check == 0 && temp->data->type == ARG)
		{
			temp->data->type = COMMAND;
			check = 1;
		}
		else if (temp->data->type == PIPE)
			check = 0;
		temp = temp->next;
	}
}
