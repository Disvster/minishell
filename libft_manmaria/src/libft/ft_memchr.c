/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:02:29 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/10 17:10:06 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	p_c;

	p_s = (unsigned char *)s;
	p_c = (char)c;
	while (n)
	{
		if (*p_s == p_c)
			return (p_s);
		p_s++;
		n--;
	}
	return (NULL);
}
