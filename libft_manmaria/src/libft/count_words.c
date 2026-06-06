/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:55:46 by manmaria          #+#    #+#             */
/*   Updated: 2025/09/16 19:56:13 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

size_t	count_words(char const *s, char c)
{
	size_t	cw;

	cw = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			cw++;
		while (*s != c && *s)
			s++;
	}
	return (cw);
}
