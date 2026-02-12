/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:10:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/02/05 18:11:06 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	parsing(t_shell	*shell)
{
	shell->token_list = lexing(shell->lineread);

	return (1);
}

void	set_types(t_token *token_list)
{
	t_token *temp;

	temp = token_list;
	while (temp)
	{	
	} //unfinished, need to study a bit better the order between expansion and type setting. should be simple tho.
}
