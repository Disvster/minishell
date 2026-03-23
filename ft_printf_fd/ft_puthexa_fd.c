/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:19:55 by rodmorei          #+#    #+#             */
/*   Updated: 2025/05/26 19:08:30 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	ft_puthexa_fd(int fd, unsigned int hex, char format)
{
	char	*lhexchars;
	char	*uhexchars;

	lhexchars = "0123456789abcdef";
	uhexchars = "0123456789ABCDEF";
	if (hex < 16)
	{
		if (format == 'x')
			write(fd, &lhexchars[hex], 1);
		else if (format == 'X')
			write(fd, &uhexchars[hex], 1);
	}
	else if (hex >= 16)
	{
		ft_puthexa_fd(fd, hex / 16, format);
		ft_puthexa_fd(fd, hex % 16, format);
	}
	return (ft_hexacount_fd(hex));
}

int	ft_hexacount_fd(unsigned int hex)
{
	int	count;

	count = 1;
	while (hex >= 16)
	{
		hex = hex / 16;
		count ++;
	}
	return (count);
}
