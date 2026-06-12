/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_restore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 21:01:00 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/12 21:01:53 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	save_parent_fds(t_shell *sh, bool in_fork)
{
	if (in_fork == true)
	{
		if (sh->saved_fds[0] >= 0)
			close(sh->saved_fds[0]);
		if (sh->saved_fds[1] >= 0)
			close(sh->saved_fds[1]);
		if (sh->saved_fds[2] >= 0)
			close(sh->saved_fds[2]);
		sh->saved_fds[0] = dup(STDIN_FILENO);
		sh->saved_fds[1] = dup(STDOUT_FILENO);
		sh->saved_fds[2] = dup(STDERR_FILENO);
		if (sh->saved_fds[0] < 0 || sh->saved_fds[1] < 0
			|| sh->saved_fds[2] < 0)
			perror("dup");
	}
	else
	{
		sh->saved_fds[0] = -1;
		sh->saved_fds[1] = -1;
		sh->saved_fds[2] = -1;
	}
}

void	restore_g_sig(t_shell *sh)
{
	if (g_sig == 130)
	{
		g_sig = 0;
		sh->exit_code = 130;
	}
	if (g_sig == 141)
	{
		g_sig = 0;
		sh->exit_code = 141;
	}
	return ;
}

void	restore_fds(t_shell *sh)
{
	int	*saved;

	saved = sh->saved_fds;
	if (saved[0] >= 0)
	{
		if (dup2(saved[0], STDIN_FILENO) < 0)
			perror("dup2");
		close(saved[0]);
		saved[0] = -1;
	}
	if (saved[1] >= 0)
	{
		if (dup2(saved[1], STDOUT_FILENO) < 0)
			perror("dup2");
		close(saved[1]);
		saved[1] = -1;
	}
	if (saved[2] >= 0)
	{
		if (dup2(saved[2], STDERR_FILENO) < 0)
			perror("dup2");
		close(saved[2]);
		saved[2] = -1;
	}
}

