/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:27:25 by rodmorei          #+#    #+#             */
/*   Updated: 2026/04/29 01:40:34 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <stdarg.h>
# include <unistd.h>

void	ft_printf_fd(int fd, const char *format, ...);
int		ft_printflag_fd(int fd, char flag, va_list args);
int		ft_putptr_fd(int fd, unsigned long hex);
int		ft_putlonghexa_fd(int fd, unsigned long hex);
int		ft_longhexacount_fd(unsigned long hex);
int		ft_nbrsize_fd(int nb);
int		ft_unsnbrsize_fd(unsigned int nb);
int		ft_putunsnbr_fd(int fd, unsigned int nb);
int		ft_puthexa_fd(int fd, unsigned int hex, char format);
int		ft_hexacount_fd(unsigned int hex);

// DEFINING MACROS:
# define ERR_QUOTES "Error: Unmatched quotes\n"
# define ERR_SYNTAX "Error: Syntax error near unexpected token ´%c'\n"
# define ERR_MALLOC "Error: Memory allocation failed\n"

#endif
