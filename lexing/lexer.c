/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:35:09 by manmaria          #+#    #+#             */
/*   Updated: 2026/02/02 17:35:19 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*lexer(char *rd_l, t_token **tokens)
{
	t_token	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (rd_l[i])
	{
		i += skip_wsp(&rd_l[i]);
		j = token_len(&rd_l[i]);
	}
}
