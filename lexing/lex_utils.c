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

int	token_lenght(char *line)
{
	int	i;

	i = 0;
	return (i);
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32
			|| (line[i] >= 9 && line[i] <= 13)))
		i++;
	return (i);
}
