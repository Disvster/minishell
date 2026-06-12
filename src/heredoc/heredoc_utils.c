/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:25:05 by rodmorei          #+#    #+#             */
/*   Updated: 2026/06/10 16:20:26 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"

int	read_heredoc_token(t_shell *sh, t_token	*tok, int *pipefds)
{
	int	write_fd;
	int	read_fd;
	int	stdin_backup;
	int	heredoc_return;

	write_fd = pipefds[1];
	read_fd = pipefds[0];
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup < 0)
	{
		perror("dup");
		close(read_fd);
		close(write_fd);
		return (1);
	}
	heredoc_return = 0;
	if (tok->next->has_quotes)
		heredoc_return = read_hdc_quoted(tok->next->content, write_fd, sh);
	else if (!tok->next->has_quotes)
		heredoc_return = read_hdc_unquoted(tok->next->content, write_fd, sh);
	handle_signal();
	close(pipefds[1]);
	if (dup2(stdin_backup, STDIN_FILENO) < 0)
		perror("dup2");
	close(stdin_backup);
	if (heredoc_return != 0)
	{
		sh->exit_code = heredoc_return;
		close (read_fd);
	}
	else
		tok->heredoc_fd = read_fd;
	return (heredoc_return);
}
