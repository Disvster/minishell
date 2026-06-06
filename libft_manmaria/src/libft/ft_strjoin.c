/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:09:05 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/11 18:40:24 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	ltotal;
	char	*scat;

	if (!s1)
		return (0);
	ltotal = ft_strlen(s1) + ft_strlen(s2);
	scat = (char *)malloc(sizeof(char) * (ltotal + 1));
	if (!scat)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		scat[i] = s1[i];
		i++;
	}
	while (i < ltotal)
	{
		scat[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	scat[i] = '\0';
	return (scat);
}
