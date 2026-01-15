/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:23:51 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/18 12:24:11 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	error_exit(t_pipex *pipex, t_cmd *cmd, int exit_code)
{
	if (cmd->path)
		free(cmd->path);
	if (cmd->args)
		free_split(cmd->args);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (close(pipex->fds[0]) == -1)
		exit(exit_code);
	if (close(pipex->fds[1]) == -1)
		exit(exit_code);
	exit(exit_code);
}

char	*pipex_strjoin(char *path, char *cmd)
{
	char	*new_cmd;
	size_t	len;
	size_t	path_len;

	path_len = ft_strlen(path);
	len = path_len + ft_strlen(cmd) + 2;
	new_cmd = ft_calloc(len, sizeof(char));
	if (!new_cmd)
		return (NULL);
	ft_strlcpy(new_cmd, path, len);
	new_cmd[path_len] = '/';
	ft_strlcpy(new_cmd + path_len + 1, cmd, len - path_len - 1);
	return (new_cmd);
}
