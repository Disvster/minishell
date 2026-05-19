/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:40:53 by rodmorei          #+#    #+#             */
/*   Updated: 2026/05/10 23:19:17 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	syntax_check(t_shell *shl)
{
	if (!pipe_checker(shl->tokens))
		return (0);
	return (1);
}

int	pipe_checker(t_token *tok)
{
	t_token	*temp;

	temp = tok;
	while (temp)
	{
		if ((!temp->prev || !temp->next) && temp->type == PIPE)
			return (0);
		if (((temp->type >= APPEND && temp->type <= OUTFILE) || temp->type == PIPE)
			&& temp->next && temp->next->type == PIPE)
			return (0);
		if ((temp->type >= APPEND && temp->type <= OUTFILE)	&& temp->next
			&& (temp->next->type >= APPEND && temp->next->type <= OUTFILE))
			return (0);
		temp = temp->next;
	}
	return (1);
}
