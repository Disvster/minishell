/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:15:47 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/15 19:40:48 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	find_specials(t_line *line, char **split)
{
	int	i;
	int	j;
	int	single_q;
	int	double_q;
	char *specials;

	i = -1;
	single_q = 0;
	double_q = 0;
	specials = "$<'\">|";
	while (split[++i])
	{
		if (ft_checksep(split[i][0], specials))
			line->spec_count++;
	}
	i = -1;
	line->specs = ft_calloc(sizeof(char *), (line->spec_count + 1));
	if (!line->specs)
		return (-1);
	j = 0;
	while (split[++i])
	{
		if (ft_checksep(split[i][0], specials))
		{
			if (split[i][0] == '<' && split[i][1] == '<')
				line->specs[j] = ft_strdup("<<");
			else if (split[i][0] == '>' && split[i][1] == '>')
				line->specs[j] = ft_strdup("<<");
			else if (split[i][0] == '\'')
			{
				line->specs[j] = ft_strdup(&split[i][0]);
				single_q++;
				if (single_q == 2)
					line->single_q = true;
			}
			else if (split[i][0] == '\"')
			{
				line->specs[j] = ft_strdup(&split[i][0]);
				double_q++;
				if (double_q == 2)
					line->double_q = true;
			}
			else
				line->specs[j] = ft_strdup(&split[i][0]);
			j++;
		}
	}
	return (1);
}
