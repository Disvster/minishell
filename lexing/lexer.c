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

t_token	*tokenizer(char *lineread, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = NULL;
	j = token_length(lineread + *i);
	if (j > 0 && !is_meta(lineread[*i]))
	{
		token = init_token(ft_substr(lineread, *i, j));
		if (!token)
			return (NULL);
		*i += j;
	}
	else if (is_meta(lineread[*i]))
	{
		token = meta_token(lineread[*i]);
	}
	// token->has_quotes = 
	// token->content = 
	// token->cmd = 
	// token->type = 
	return (token);
}

void *lexing(char **envp, char *lineread)
{
	t_dlist	*lexer;
	t_dlist	*new_node;
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
		token = tokenizer(lineread, &i);
		// TODO:
		// if (!token) || if (tokenizer(&token, lineread, &i))
		// 	return (dlist_list_clear(lexer, function_that_clears_t_token_vars));
		// 	se o token existir liberta o que esta dentro do token e depois 
		// 	liberta o token em si
		new_node = dlist_new_node(token);
		if (!lexer)
			lexer = new_node;
		else
			dlist_add_last(&lexer, new_node);
	}
	return (NULL);
}
