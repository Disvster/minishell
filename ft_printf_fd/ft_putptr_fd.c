/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:37:10 by rodmorei          #+#    #+#             */
/*   Updated: 2025/05/26 19:09:14 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	ft_putptr_fd(int fd, unsigned long hex)
{
	int	binted;

	binted = 0;
	if (hex == 0)
		return (write(fd, "(nil)", 5));
	write(1, "0x", 2);
	binted += ft_putlonghexa_fd(fd, hex);
	return (binted);
}

int	ft_putlonghexa_fd(int fd, unsigned long hex)
{
	char	*hexchars;

	hexchars = "0123456789abcdef";
	if (hex < 16)
	{
		write(fd, &hexchars[hex], 1);
	}
	else if (hex >= 16)
	{
		ft_putlonghexa_fd(fd, hex / 16);
		ft_putlonghexa_fd(fd, hex % 16);
	}
	return (ft_longhexacount_fd(hex));
}

int	ft_longhexacount_fd(unsigned long hex)
{
	int	count;

	count = 3;
	while (hex >= 16)
	{
		hex = hex / 16;
		count ++;
	}
	return (count);
}
/*
#include <stdio.h>
int	main (void)
{
	char s = 'a';
	char	*c = &s;
	printf("\n %d", ft_putptr_pf((unsigned long)c));
	return (0);
}*/
