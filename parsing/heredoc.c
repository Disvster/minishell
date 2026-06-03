/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:58:26 by rodmorei          #+#    #+#             */
/*   Updated: 2026/06/03 22:44:09 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int handle_heredoc_tokens(t_shell *sh, t_token *tokens)
{
	t_token *tok;
	int     pipefd[2];

	tok = tokens;
	while (tok)
	{
		if (tok->type == HEREDOC)
		{
			if (!tok->next || tok->next->type != LIMITER)
				return (ft_printf_fd(2, ERR_DELIMITER), sh->exit_code = 2, -1);
			if (pipe(pipefd) < 0)
				return (ft_printf_fd(2, ERR_PIPE), sh->exit_code = 1, -1);
			if (read_heredoc_input(tok->next->content, pipefd[1]) < 0)
				return (close(pipefd[1]), sh->exit_code = 1, -1);
			close(pipefd[1]);
			tok->heredoc_fd = pipefd[0];
		}
		tok = tok->next;
	}
	return (0);
}

int read_heredoc_input(const char *delimiter, int write_fd)
{
	char *line;

	signal(SIGINT, handle_heredoc_signal);
	while (1)
    {
        line = readline("> ");
        if (!line)
            return (ft_printf_fd(2, WARNING_HEREDOC, delimiter), 0);
        if (ft_strcmp(line, delimiter) == 0)
		{
            free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	return (0);
}

int	apply_heredoc(int heredoc_fd)
{
	if (heredoc_fd < 0)
	{
		ft_printf_fd(2, "[minishell] Error : heredoc - invalid fd\n");
		return (-1);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		ft_printf_fd(2, "[minishell] Error : dup 2 failed\n");
		close(heredoc_fd);
		return (-1);
	}
	close(heredoc_fd);
	return (0);
}
