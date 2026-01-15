/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:15:47 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/15 18:38:35 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	check_sep(char const c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

int	find_specials(t_line *line, char **split, int *id)
{
	int	i;
	char *specials;

	i = -1;
	specials = "$<\'\">";
	while (split[++i])
	{
		if (check_sep(split[i][0], specials))
			line->spec_count++;
	}
	i = -1;
	line->specs = ft_calloc(sizeof(char *), (line->spec_count + 1));
	if (!line->specs)
		return (-1);
	while (split[++i])
	{
		if (check_sep(split[i][0], specials))
		{
			if (split[i][0] == '<' && split[i][1] == '<')
				line->spec = ft_strdup("<<")
			if (split[i][0] == '<' && split[i][1] == '<')
				line->spec = ft_strdup("<<")
		}
	}
}
