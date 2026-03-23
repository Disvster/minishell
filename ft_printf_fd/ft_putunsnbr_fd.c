/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsnbr_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:04:43 by rodmorei          #+#    #+#             */
/*   Updated: 2025/05/26 19:04:10 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/ft_printf_fd.h"

int	ft_putunsnbr_fd(int fd, unsigned int nb)
{
	int	temp;

	if (nb < 10)
	{
		temp = nb + '0';
		write(fd, &temp, 1);
	}
	else if (nb >= 10)
	{
		ft_putunsnbr_fd(fd, nb / 10);
		ft_putunsnbr_fd(fd, nb % 10);
	}
	return (ft_unsnbrsize_fd(nb));
}

int	ft_unsnbrsize_fd(unsigned int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}
/*
#include <stdio.h>
int	main (void)
{
	unsigned int	ye = 3232481932;
	printf("\n %u", ft_putunsnbr_pf(ye));
	return (0);
}*/
