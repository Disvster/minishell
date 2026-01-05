/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:31:28 by manmaria          #+#    #+#             */
/*   Updated: 2025/05/15 23:10:31 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	3
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line_bonus.h"

char	*get_next_line(int fd);
char	*ft_strdup_gnl(const char *src);
char	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*ft_trimbuffer(char *buf);
size_t	ft_strclen(const char *s, int c);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);

#endif
