/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:26:03 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/15 19:45:31 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static size_t	count_digit(long nu)
{
	size_t	len;

	len = 1;
	if (nu < 0)
	{
		nu *= -1;
		len++;
	}
	while (nu >= 10)
	{
		nu /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*numb;
	long	nu;
	size_t	len;

	nu = n;
	len = count_digit(nu);
	numb = (char *)malloc(sizeof(char) * (len + 1));
	if (!numb)
		return (NULL);
	numb[len] = '\0';
	if (nu < 0)
	{
		nu *= -1;
		numb[0] = '-';
	}
	while (nu >= 10)
	{
		numb[len-- - 1] = (nu % 10) + 48;
		nu /= 10;
	}
	numb[len - 1] = nu + 48;
	return (numb);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	int n = ft_atoi(av[1]);
	char *numb = ft_itoa(n);
	(void)ac;
	printf("ft_itoa -> %s\n", numb);
	return (0);
}*/
