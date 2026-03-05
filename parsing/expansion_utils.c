/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:45:38 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/05 18:00:47 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

void	append_quoted(t_shell *shl, t_token	*token, char *new, int	*index)
{
	int	i;
	int	quote;
	char	*str;

	i = *index;
	str = token->content;
	quote = str[i++];

	while (str[i] && str[i] != quote)
	{
		if (quote == '"' && str[i] == '$' && str[i] &&
				!ft_isspace(str[i + 1]) && str[i + 1] != quote)
			append_expand(shl, token, new, &i);
		else
			append_letter(new, str[i], &i);
	}
}

void	append_expand(t_shell *shl, t_token *token, char *new, int *index)
{
}
