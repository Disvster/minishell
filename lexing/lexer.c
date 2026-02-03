/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:35:09 by manmaria          #+#    #+#             */
/*   Updated: 2026/02/03 20:22:34 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*tokenizer(char *rd_l, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = ft_calloc(1, sizeof(t_token));
	while (rd_l[*i])
	{
		*i += skip_whitespace(&rd_l[*i]);
		j = token_length(&rd_l[*i]);
		if (j > 0 && !is_meta(rd_l[*i]))
		{
			token = init_token(ft_substr(rd_l, *i, j));
			if (!token)
				return (NULL);
			*i += j;
		}
		else if (is_meta(rd_l[*i]))
		{
			token = meta_token(rd_l[*i]);
		}
	}
	// token->has_quotes = 
	// token->content = 
	// token->cmd = 
	// token->type = 
	return (token);
}

void *lexing(char **envp, char *readline)
{
	t_dlist	*lexer;
	t_dlist	*new_node;
	t_token	*token;
	int		i;

	i = 0;
	lexer = NULL;
	while (readline[i])
	{
		token = tokenizer(readline, &i);
		// TODO:
		// if (!token) || if (tokenizer(&token, readline, &i))
		// 	return (dlist_list_clear(lexer, function_that_clears_t_token_vars));
		// 	se o token existir liberta o que esta dentro do token e depois 
		// 	liberta o token em si
		new_node = dlist_new_node(&token);
		if (!lexer)
			lexer = new_node;
		else
			dlist_add_last(&lexer, new_node);
	}
	return (NULL);
}
