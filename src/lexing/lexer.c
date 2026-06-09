/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:35:09 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/22 21:31:49 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int tokenizer(t_token **final, char *lineread, int *i, int *err_code)
{
	t_token	*token;
	int		j;

	j = 0;
	token = NULL;
	j = token_length(lineread + *i);
	if (j < 0)
		return (*err_code = 2, ft_printf_fd(2, ERR_QUOTES), 1);
	if (j > 0 && !is_meta(lineread[*i]))
	{
		token = init_token(ft_substr(lineread, *i, j));
		if (!token)
			return (*err_code = 1, ft_printf_fd(2, ERR_MALLOC), 1);
		*i += j;
	}
	else if (is_meta(lineread[*i]))
	{
		token = meta_token(lineread + *i, &j);
		if (!token)
			return (*err_code = 2, 1);
		*i += j;
	}
	*final = token;
	return (0);
}

int	lexing(t_token **final, char *lineread, int *err_code)
{
	t_token	*lexer;
	t_token	*token;
	int		i;

	i = 0;
	lexer = NULL;
	token = NULL;
	while (lineread[i])
	{
		i += skip_whitespace(lineread + i);
		if (!lineread[i])
			break ;
		if (tokenizer(&token, lineread, &i, err_code) != 0)
			return (tokenlist_clear(&lexer), 1);
		token->prev = NULL;
		token->next = NULL;
		tokenlist_add_last(&lexer, token);
	}
	*final = lexer;
	return (0);
}
