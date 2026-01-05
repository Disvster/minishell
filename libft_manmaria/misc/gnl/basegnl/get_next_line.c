/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:30:39 by manmaria          #+#    #+#             */
/*   Updated: 2025/05/15 23:10:26 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/get_next_line.h"

int	find_line(char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s == '\n')
			return (0);
		s++;
	}
	return (1);
}

char	*ft_trimstash(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	len = ft_strclen(stash, '\n');
	if (stash[len] == '\n')
		len++;
	line = ft_calloc_gnl(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	return (line);
}

char	*ft_stash_copycat(char *stash, char **buffer)
{
	char	*tmp;
	size_t	stash_len;
	size_t	buffer_len;
	size_t	i;

	stash_len = ft_strclen(stash, 0);
	buffer_len = ft_strclen(*buffer, 0);
	tmp = ft_calloc_gnl(sizeof(char), stash_len + buffer_len + 1);
	if (!tmp)
		return (free(*buffer), free(stash), NULL);
	i = -1;
	if (stash)
	{
		while (++i < stash_len)
			tmp[i] = stash[i];
		free(stash);
	}
	i = stash_len - 1;
	while (++i < (stash_len + buffer_len))
		tmp[i] = (*buffer)[i - stash_len];
	free(*buffer);
	*buffer = NULL;
	return (tmp);
}

char	*ft_free_stash(char **stash, char *line, ssize_t bread)
{
	char	*n_stash;
	size_t	flen;

	if (!line || bread <= 0)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (line);
	}
	flen = ft_strclen(*stash, 0) - ft_strclen(line, 0);
	n_stash = ft_substr_gnl(*stash, ft_strclen(line, 0), flen);
	free(*stash);
	*stash = NULL;
	if (!n_stash)
		return (free(line), NULL);
	*stash = n_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		bread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash, NULL, 0));
	bread = 1;
	line = NULL;
	buffer = NULL;
	while (bread > 0 && find_line(stash))
	{
		buffer = ft_calloc_gnl(sizeof(char), BUFFER_SIZE + 1);
		if (!buffer)
			return (ft_free_stash(&stash, NULL, 0));
		bread = read(fd, buffer, BUFFER_SIZE);
		if (bread > 0)
			stash = ft_stash_copycat(stash, &buffer);
		else
			free (buffer);
		if (!stash || bread == -1)
			return (ft_free_stash(&stash, NULL, bread));
	}
	line = ft_trimstash(stash);
	return (ft_free_stash(&stash, line, bread));
}
