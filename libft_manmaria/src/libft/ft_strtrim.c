/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:41:40 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/14 13:42:46 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static int	is_charset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	size_t	j;

	if (!s1)
		return (NULL);
	while (is_charset(*s1, set) && *s1)
		s1++;
	j = ft_strlen(s1);
	while (is_charset(s1[j - 1], set))
		j--;
	strim = ft_substr(s1, 0, j);
	return (strim);
}
