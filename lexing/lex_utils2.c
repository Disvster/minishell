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
	{  // NOTE: maybe change these function calls to just be ft_printf_fd
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(ch, 2);
		if (*j > 3)
			ft_putchar_fd(ch, 2);
		ft_putstr_fd("'\n", 2);
		return (NULL);
	}
}
