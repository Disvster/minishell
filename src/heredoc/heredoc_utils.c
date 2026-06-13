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

static int	hdc_stdin_backup_error(int *read_fd, int *write_fd)
{
	perror("dup");
	close(*read_fd);
	close(*write_fd);
	return (1);
}

static void	hdc_fds_init(int *write_fd, int *read_fd, int *stdin_backup,
	int *pipefds)
{
	*write_fd = pipefds[1];
	*read_fd = pipefds[0];
	*stdin_backup = dup(STDIN_FILENO);
}

static void	hdc_quote_check(int *heredoc_return, t_token *tok, int write_fd,
	t_shell *sh)
{
	*heredoc_return = 0;
	if (tok->next->has_quotes)
		*heredoc_return = read_hdc_quoted(tok->next->content, write_fd, sh);
	else if (!tok->next->has_quotes)
		*heredoc_return = read_hdc_unquoted(tok->next->content, write_fd, sh);
}

int	read_heredoc_token(t_shell *sh, t_token	*tok, int *pipefds)
{
	int	write_fd;
	int	read_fd;
	int	stdin_backup;
	int	heredoc_return;

	hdc_fds_init(&write_fd, &write_fd, &stdin_backup, pipefds);
	if (stdin_backup < 0)
		return (hdc_stdin_backup_error(&read_fd, &write_fd));
	hdc_quote_check(&heredoc_return, tok, write_fd, sh);
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
