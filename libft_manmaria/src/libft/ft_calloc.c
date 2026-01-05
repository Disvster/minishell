/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:18:43 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/10 19:49:01 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	mult;

	if (nmemb != 0 && size != 0 && (nmemb > ((size_t)-1 / size)))
		return (NULL);
	mult = nmemb * size;
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, mult);
	return (arr);
}
