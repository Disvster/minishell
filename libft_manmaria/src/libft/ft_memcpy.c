/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:32:03 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/09 16:02:43 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char		*p_src;
	unsigned char			*p_dest;
	size_t					i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	p_src = src;
	p_dest = dest;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}
