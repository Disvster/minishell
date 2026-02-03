/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:27:22 by manmaria          #+#    #+#             */
/*   Updated: 2026/02/02 17:34:09 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	token_length(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'' && quote == 0)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
			{
				i++;
				quote = 0;
			}
			continue;
		}
		if (!quote && (is_meta(line[i]) || ft_isspace(line[i])))
			break;
		i++;
	}
	return (i);
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	is_meta(char ch)
{
	return (ch == '|' || ch == '>' || ch == '<');
}

t_token	*init_token(char *content)
{
	t_token	*temp;

	if (!content)
		return (NULL);
	temp = ft_calloc(1, sizeof(t_token));
	if (!temp)
		return (free(content), NULL);
	if (exist_quotes(content))
		temp->has_quotes = true;
	else
		temp->has_quotes = false;
	temp->content = content;
	temp->type = ARG;// TODO: in parsing
	return (temp);
}

int	exist_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (line[i] == '"' || line[i] == '\'')
			return (1);
	return (0);
}
