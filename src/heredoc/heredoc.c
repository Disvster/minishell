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

#include "../../incs/minishell.h"

int	handle_heredoc_tokens(t_shell *sh, t_token *tokens)
{
	t_token	*tok;
	int		pipefd[2];

	tok = tokens;
	while (tok)
	{
		if (tok->type == HEREDOC)
		{
			if (!tok->next || tok->next->type != LIMITER)
				return (ft_printf_fd(2, ERR_DELIMITER), sh->exit_code = 2, -1);
			if (pipe(pipefd) < 0)
				return (ft_printf_fd(2, ERR_PIPE), sh->exit_code = 1, -1);
			if  (tok->next->has_quotes && read_heredoc_input_quoted(tok->next->content, pipefd[1]) != 0)
				return (close(pipefd[1]), sh->exit_code = 1, -1);
			if  (!tok->next->has_quotes && read_heredoc_input_unquoted(tok->next->content, pipefd[1], sh) != 0)
				return (close(pipefd[1]), sh->exit_code = 1, -1);
			close(pipefd[1]);
			tok->heredoc_fd = pipefd[0];
		}
		tok = tok->next;
	}
	return (0);
}

int	read_heredoc_input_unquoted(const char *delimiter, int write_fd, t_shell *sh)
{
	char	*line;
	int	i;

	line = NULL;
	i = 0;
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
		i = 0;
		while (line[i])
			write_expanded(write_fd, &line[i], sh, &i);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	return (0);
}

int	read_heredoc_input_quoted(const char *delimiter, int write_fd)
{
	char	*line;

	line = NULL;
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

int	write_expanded(int	fd, char *str, t_shell *shl, int *index)
{
	char *temp;

	temp = NULL;
	if (str[0] != '$')
	{
		write (fd, str, 1);
		return (*index += 1, 0);
	}
	if (str[1] && (is_edge(str[1]) || ft_isdigit(str[1])))
		return (*index += 2, 0);
	if (!ft_isalpha(str[1]))
	{
		write(fd, "$", 1);
		return (*index += 1, 0);
	}
	*index += 1;
	temp = env_identifier(shl, &str[1], index);
	if (!temp)
		return (ft_printf_fd(2, ERR_MALLOC), 1);
	ft_putstr_fd(temp, fd);
	return (0);
}
