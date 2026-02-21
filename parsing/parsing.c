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

void	set_types(t_dlist *tlist)
{
	t_dlist *temp;
	int	len;

	len = 0;
	temp = tlist;
	while (temp)
	{
		len = ft_strlen(temp->data->content);
		if (ft_strncmp(temp->data->content, "<<", len) == 0 && !temp->data->has_quotes)
			temp->data->type = HEREDOC;
		else if (ft_strncmp(temp->data->content, ">>", len) == 0 && !temp->data->has_quotes)
			temp->data->type = APPEND;
		else if (ft_strncmp(temp->data->content, "<", len) == 0 && !temp->data->has_quotes)
			temp->data->type = INFILE;
		else if (ft_strncmp(temp->data->content, ">", len) == 0 && !temp->data->has_quotes)
			temp->data->type = OUTFILE;
		else if (ft_strncmp(temp->data->content, "|", len) == 0 && !temp->data->has_quotes)
			temp->data->type = PIPE;
		else if (temp->prev && temp->prev->data->type == HEREDOC)
			temp->data->type = LIMITER;
		else if (temp->prev && (temp->prev->data->type == INFILE || temp->prev->data->type == OUTFILE
				|| temp->prev->data->type == APPEND))
			temp->data->type = TFILE;
		temp = temp->next;
	}
}

void	set_commands(t_dlist *tlist)
{
	t_dlist *temp;
	int	check;

	temp = tlist;
	check = 0;

	while (temp)
	{
		if (check == 0 && temp->data->type == ARG)
		{
			temp->data->type = COMMAND;
			check = 1;
		}
		else if (temp->data->type == PIPE)
			check = 0;
		temp = temp->next;
	}
}

char *expand(t_token *token, t_shell *shl)
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
