/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:45:31 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/31 23:41:22 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Example:
// $ < Makefile < main.c grep "a" file.txt >> test.txt > matches.txt
// INFILE (<) -> TFILE(Makefile)
// INFILE (<) -> TFILE(main.c)
// COMMAND(grep) -> ARG1("a") -> ARG2(file.txt)
// OUTFILE(>>) -> TFILE(test.txt)
// OUTFILE(>) -> TFILE(matches.txt)

// t_cmd* {
//	char	*path = /usr/bin/grep ;
//	char	**args = {"/usr/bin/grep", "a", "file.txt"};
//	int		arg_count = 2;
//	t_redir	*redirs = {
//				{[0]
//					int	 type = INFILE;
//					char *filename = "Makefile"; //Check access()
//					int	 fd = open(Makefile, RDONLY);
//				};
//				{[1]
//					int type = INFILE;
//					char *filename = "main.c"; //Check access()
//					int	 fd = open(main.c, RDONLY);
//				};
//				{[2]
//					int type = APPEND;
//					char *filename = "test.txt"; //Check access()
//					int	 fd = open(matches.txt, WRITE?);
//				};
//				{[3]
//					int type = OUTFILE;
//					char *filename = "matches.txt"; //Check access()
//					int	 fd = open(matches.txt, WRITE?);
//				};
//			}
//	}
//	Order of redirection parsing
//     [0]         [1]          {cmd}                [2]             [3]
//(< Makefile) (< main.c ) {grep "a" file.txt} ( >> test.txt ) ( > matches.txt )
//	char *infile = "main.c"
//	char *outfile = "matches.c"

#include "../incs/executor.h"

static int	count_redirects(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)// WARNING: heredoc
			count++;
		tmp = tmp->prev;
	}
	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)// WARNING: heredoc
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	traverse_back(t_token *token, t_cmd *cmd, int *i)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp && tmp->type != PIPE && *i < cmd->redirect_count)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd->redirs[*i].type = tmp->type;
			if (tmp->next && tmp->next->type == TFILE)
				cmd->redirs[*i].filename = tmp->next->content;
			else
				cmd->redirs[*i].filename = NULL;
			(*i)++;
		}
	}
}

static void	traverse_forward(t_token *token, t_cmd *cmd, int *i)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != PIPE && *i < cmd->redirect_count)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			cmd->redirs[*i].type = tmp->type;
			if (tmp->next && tmp->next->type == TFILE)
				cmd->redirs[*i].filename = tmp->next->content;
			else
				cmd->redirs[*i].filename = NULL;
			(*i)++;
		}
		tmp = tmp->next;
	}
}

void	populate_redirects(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->redirect_count = count_redirects(token);
	if (cmd->redirect_count == 0)
		return ;
	cmd->redirs = ft_calloc(cmd->redirect_count, sizeof(char **));
	if (!cmd->redirs)
		return (ft_printf_fd(2, "malloc error on redirect array"));
	traverse_back(token, cmd, &i);
	traverse_forward(token, cmd, &i);
}

static int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	open_append_or_outfile(char *filename, int type)
{
	int	fd;

	if (type == OUTFILE)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("minishell"), -1);
	}
	else if (type == APPEND)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("minishell"), -1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirects(t_cmd *cmd)
{
	int	i;
	int	outfd;
	int	type;

	i = 0;
	while (i < cmd->redirect_count)
	{
		type = cmd->redirs[i].type;
		if (type == INFILE)
		{
			if (open_infile(cmd->redirs[i].filename) < 0)
				return (-1);
		}
		else if (type == OUTFILE || type == APPEND)
		{
			if (open_append_or_outfile(cmd->redirs[i].filename, type) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
