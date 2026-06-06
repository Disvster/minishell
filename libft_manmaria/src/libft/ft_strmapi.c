/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:48:47 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/15 19:57:48 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	size_t			i;

	i = ft_strlen(s);
	mapi = (char *)malloc(sizeof(char) * (i + 1));
	if (!mapi)
		return (NULL);
	mapi[i] = '\0';
	while (i-- > 0)
		mapi[i] = f(i, s[i]);
	return (mapi);
}
