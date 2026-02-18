/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 18:10:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/02/18 20:28:53 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	parsing(t_shell	*shell)
{
	shell->tokens = lexing(shell->lineread);

	return (1);
}

void	set_types(t_token *token_list)// WARNING: t_dlist here maybe?
{
	t_token *temp;

	temp = token_list;
	while (temp)
	{	
	} //unfinished, need to study a bit better the order between expansion and type setting. should be simple tho.
}

char *expand(t_token *token)
{
	char	*s;
	char	*new;
	int		new_len;
	int		quote;

	if (!token->content)
		return (NULL);
	s = token->content;
	quote = 0;

	// new = ft_calloc(ft_strlen(s), sizeof(char)); // TODO:
	// if (!new)
	// 	return (NULL);

	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			if (quote == 0)
				quote = *s++;
			else if (quote == *s)
				s++;
		}
		if (*s == '$')
	/* $PAGER=less
	$> echo 'ola"$PAGER"More'
	ola"$PAGER"More
	$> echo "ola'$PAGER'More"
	ola'less'More
	*/

		{//				     $[ENV]        len of capitalized word
			while (ft_strncmp(s + 1, *envp, env_len(s + 1)))
				envp++;
			if (*envp)
			{
				while (**envp != '=')
					*envp++;
				new_len += ft_strlen(*envp);
				s++;
				s += env_len(s);
			}
		}
		new_len++;
		s++;
	}
	// isto tudo (que ta pra cima) so para calcular o tamanho da string final do token
	// depois e repetir o processo mas a mandar para um novo char *token_string;
	// WARNING: posso tar doing too much e isto ser mais simples
	
		// new[i] = s[i];// TODO:
	
	return ();
}
