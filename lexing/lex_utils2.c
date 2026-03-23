/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:05:30 by rodmorei          #+#    #+#             */
/*   Updated: 2026/02/03 18:24:00 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*meta_token(char *lineread, int *j)
{
	char	ch;

	ch = *lineread;
	while (lineread[*j] && lineread[*j] == ch)
		*j += 1;
	if (*j <= 2)
		return (init_token(ft_substr(lineread, 0, *j)));
	else
		return (ft_printf_fd(2, ERR_SYNTAX, ch), NULL);
}

void	free_token_data(void	*token)
{
	t_token	*temp;

	temp = (t_token *)token;
	free(temp->content);
	free(temp);
	return;
}
