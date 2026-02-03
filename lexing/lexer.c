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

t_token	*tokenizer(char *rd_l, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	ft_bzero(&token, sizeof(t_token));
	while (rd_l[*i])
	{
		*i += skip_whitespace(&rd_l[*i]);
		j = token_lenght(&rd_l[*i]);
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
	token = NULL;
	while (readline[i])
	{
		token = tokenizer(readline, &i);
		// if (!token) || if (tokenizer(&token, readline, &i))
			// TODO: return (dlist_list_clear(lexer, function_that_clears_t_token_vars));
		new_node->data = token;
		if (!lexer)
			lexer = new_node;
		else
			dlist_add_last(&lexer, new_node);
	}
	return (NULL);
}
