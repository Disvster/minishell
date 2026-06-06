/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:59:41 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/06 15:00:52 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"

int	count_redirects(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC) // WARNING: heredoc
			count++;
		tmp = tmp->prev;
	}
	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC) // WARNING: heredoc
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	traverse_back(t_token *token, t_cmd *cmd, int *i)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp && tmp->type != PIPE && *i < cmd->redirect_count)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd->redirs[*i].type = tmp->type;
			cmd->redirs[*i].heredoc_fd = tmp->heredoc_fd;
			if (tmp->next && tmp->next->type == TFILE)
				cmd->redirs[*i].filename = tmp->next->content;
			else
				cmd->redirs[*i].filename = NULL;
			(*i)++;
		}
		tmp = tmp->next;
	}
}

void	traverse_forward(t_token *token, t_cmd *cmd, int *i)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE && *i < cmd->redirect_count)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd->redirs[*i].type = tmp->type;
			cmd->redirs[*i].heredoc_fd = tmp->heredoc_fd;
			if (tmp->next && tmp->next->type == TFILE)
				cmd->redirs[*i].filename = tmp->next->content;
			else
				cmd->redirs[*i].filename = NULL;
			(*i)++;
		}
		tmp = tmp->next;
	}
}

int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: ");
		return (perror(filename), -1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_printf_fd(2, "minishell: ");
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	open_append_or_outfile(char *filename, int type)
{
	int	fd;

	if (type == OUTFILE)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_printf_fd(2, "minishell: "), perror(filename), -1);
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_printf_fd(2, "minishell: "), perror(filename), -1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_printf_fd(2, "minishell: ");
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

