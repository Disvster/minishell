/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:07:42 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/11 19:32:34 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	expansion(t_token *head, t_shell *shl)
{
	t_token	*temp;
	char	*new;

	new = ft_strdup("");
	if (!new)
		return (0);
	temp = head;
	while (temp)
	{
		temp->content = expand(temp, shl, new);
		if (!temp->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}

char	*expand(t_token *token, t_shell *shl, char	*nstr)
{
	char	*s;
	int		i;

	i = 0;
	if (!token->content)
		return (NULL);
	s = token->content;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (!append_quoted(shl, token, &nstr, &i))
				return (NULL);
		}
		else if (s[i] == '$')
		{
			if (!append_expand(shl, token, &nstr, &i))
				return (NULL);
		}
		else if (!append_letter(&nstr, s[i], &i))
			return (NULL);
	}
	return (nstr);
}

int	append_quoted(t_shell *shl, t_token	*token, char **nstr, int	*i)
{
	int		quote;
	char	*str;

	str = token->content;
	quote = str[*i];
	*i += 1;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i + 1] && str[*i] == '$' && str[*i]
			&& !ft_isspace(str[*i + 1]) && str[*i + 1] != quote)
			append_expand(shl, token, nstr, i);
		else if (!append_letter(nstr, str[*i], i))
			return (0);
	}
	return (1);
}

int	append_expand(t_shell *shl, t_token *token, char **nstr, int *i)
{
	char	*str;
	char	*env_name;

	env_name = NULL;
	str = token->content;
	if (is_edge(str[*i + 1]) || ft_isdigit(str[*i + 1]))
		return (*i += 1, 1);
	if (str[*i + 1] == '"' || str[*i + 1] == '\'')
		return (*i += 1, 1);
	if (str[*i + 1] == '?')
		return (append_exit_code(nstr, shl->exit_code, i));
	if (!ft_isalpha(str[*i + 1]) && str[*i + 1] != '_')
	{
		if (!append_letter(nstr, '$', i) || !append_letter(nstr, str[*i], i))
			return (0);
		*i += 2;
		return (1);
	}
	*i += 1;
	env_name = env_identifier(shl, &str[*i], i);
	*nstr = strjoinfree(*nstr, env_name);
	if (!*nstr)
		return (0);
	return (1);
}

int	append_letter(char	**nstr, char c, int	*i)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = 0;
	*i += 1;
	*nstr = strjoinfree(*nstr, temp);
	if (!nstr)
		return (0);
	return (1);
}
