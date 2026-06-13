/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:08:06 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/13 20:32:51 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

void	init_pipeline(t_shell *sh)
{
	sh->pipeline.count = 0;
	sh->pipeline.prev_read = -1;
	ft_memset(sh->pipeline.pids, -1, 1024 * sizeof(pid_t));
}

int	setup_pipes_and_fork(t_shell *sh, t_cmd *curr, int *pipefd)
{
	pid_t	pid;

	if (curr->next)
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe");
			if (sh->pipeline.prev_read != -1)
				close(sh->pipeline.prev_read);
			return (-1);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (curr->next)
			(close(pipefd[0]), close(pipefd[1]));
		if (sh->pipeline.prev_read != -1)
			close(sh->pipeline.prev_read);
		return (-1);
	}
	return (pid);
}

void	dup_and_close_pipefds(t_shell *sh, t_cmd *curr, int *pipefd)
{
	if (sh->pipeline.prev_read != -1)
	{
		if (dup2(sh->pipeline.prev_read, STDIN_FILENO) < 0)
		{
			perror("dup2");
			cleanup_and_exit(1, sh, curr);
		}
		close(sh->pipeline.prev_read);
	}
	if (curr->next)
	{
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			cleanup_and_exit(1, sh, curr);
		}
		close(pipefd[READ_END]);
		close(pipefd[WRITE_END]);
	}
}
