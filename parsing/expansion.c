/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:07:42 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/06 16:07:42 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

char	*expand(t_token *token, t_shell *shl)
{
	char	*s;
	char	*new;
	int		i;

	i = 0;
	if (!token->content)
		return (NULL);
	s = token->content;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			append_quoted(shl, token, &new, &i);
		else if (s[i] == '$')
		{
			if (s[i + 1] == '"' || s[i + 1] == '\'')
			{
				i++;
				continue ;
			}
			append_expand(shl, token, &new, &i);
		}
		else
			append_letter(new, s[i], &i);
	}
	return (new);
}

void	append_quoted(t_shell *shl, t_token	*token, char **nstr, int	*index)
{
	int		i;
	int		quote;
	char	*str;

	i = *index;
	str = token->content;
	quote = str[i++];
	while (str[i] && str[i] != quote)
	{
		if (quote == '"' && str[i + 1] && str[i] == '$' && str[i]
			&& !ft_isspace(str[i + 1]) && str[i + 1] != quote)
			append_expand(shl, token, nstr, index);
		else
			append_letter(nstr, str[i], index);
	}
}

void	append_expand(t_shell *shl, t_token *token, char **nstr, int *i)
{
	char	*str;
	char	*env_name;

	env_name = NULL;
	str = token->content;
	if (is_edge(str[*i + 1]) || ft_isdigit(str[*i + 1]))
	{
		*i += 2;
		return ;
	}
	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_')
	{
		append_letter(nstr, '$', i);
		append_letter(nstr, str[*i + 1], i);
		*i += 2;
		return ;
	}
	env_name = env_identifier(shl, str[*i], i);
	*nstr = strjoinfree(*nstr, env_name);
	return ;
}
