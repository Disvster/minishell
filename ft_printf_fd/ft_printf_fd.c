/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:17:37 by rodmorei          #+#    #+#             */
/*   Updated: 2025/05/26 19:05:56 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

void	ft_printf_fd(int	fd, const char *format, ...)
{
	va_list	args;
	int		i;

	i = 0;
	if (!format)
		return ;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			ft_printflag_fd(fd, format[++i], args);
		else
			ft_putchar_fd(format[i], fd);
		i++;
	}
	return ;
}

int	ft_printflag_fd(int	fd, char flag, va_list args)
{
	int	binted;

	binted = 0;
	if (flag == 'c')
		ft_putchar_fd(va_arg(args, int), fd);
	else if (flag == 's')
		ft_putstr_fd(va_arg(args, char *), fd);
	else if (flag == 'p')
		binted += ft_putptr_fd(fd, va_arg(args, unsigned long));
	else if (flag == 'd')
		ft_putnbr_fd(fd, va_arg(args, int));
	else if (flag == 'i')
		ft_putnbr_fd(va_arg(args, int), fd);
	else if (flag == 'u')
		binted += ft_putunsnbr_fd(fd, va_arg(args, unsigned int));
	else if (flag == 'x')
		binted += ft_puthexa_fd(fd, va_arg(args, unsigned int), flag);
	else if (flag == 'X')
		binted += ft_puthexa_fd(fd, va_arg(args, unsigned int), flag);
	else if (flag == '%')
		ft_putchar_fd('%', fd);
	return (binted);
}
/*
int	main(void)
{
	ft_printf("Bom dia %d %c %u %p, %x, %X %%", 1234, 'c', 421321, 
	"Amigo", 42, 42);
	return (0);
}*/
