/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:53:03 by manmaria          #+#    #+#             */
/*   Updated: 2025/11/12 19:03:41 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strchrnul(const char *s, int c)
{
	if (s)
		while (*s)
			if (*s++ == (char)c)
				return ((char *)(s - 1));
	return ((char *)s);
}
