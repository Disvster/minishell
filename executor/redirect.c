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
//					int type = INFILE;
//					char *filename = "main.c"; //Check access()
//					int	 fd = open(main.c, RDONLY);
//				};
//				{[1]
//					int	 type = INFILE;
//					char *filename = "Makefile"; //Check access()
//					int	 fd = open(Makefile, RDONLY);
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
//     [1]         [0]          {cmd}                [2]             [3]
//(< Makefile) (< main.c ) {grep "a" file.txt} ( >> test.txt ) ( > matches.txt )
//	char *infile = "main.c"
//	char *outfile = "matches.c"

#include "../incs/executor.h"
#include "../incs/minishell.h"

static int	count_redirects(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE
			|| tmp->type == APPEND || tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	traverse_back(t_token *token, t_cmd *cmd, int *i)
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
			if (tmp->type == INFILE)
				cmd->redirs[*i].fd = STDIN_FILENO;
			else
				cmd->redirs[*i].fd = STDOUT_FILENO;
			(*i)++;
		}
		tmp = tmp->prev;
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
			if (tmp->type == INFILE)
				cmd->redirs[*i].fd = STDIN_FILENO;
			else
				cmd->redirs[*i].fd = STDOUT_FILENO;
			(*i)++;
		}
		tmp = tmp->next;
	}
}

static void	resolve_redirects(t_cmd *cmd, char **input_file, char **output_file)
{
	int		i;
	bool	infile;

	i = 0;
	infile = false;
	*input_file = NULL;
	*output_file = NULL;
	while (i < cmd->redirect_count)
	{
		if (cmd->redirs[i].type == INFILE && infile == false)
		{
			*input_file = cmd->redirs[i].filename;
			infile = true;
		}
		else if (cmd->redirs[i].type == OUTFILE
			|| cmd->redirs[i].type == APPEND)
			*output_file = cmd->redirs[i].filename;
		i++;
	}
}

void	populate_redirects(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	//redir count for alloc
	cmd->redirect_count = count_redirects(token);
	if (cmd->redirect_count == 0)
		return ;
	//alloc mem for redir array
	cmd->redirs = ft_calloc(cmd->redirect_count, sizeof(char **));
	if (!cmd->redirs)
		return (ft_printf_fd(2, "malloc error on redirect array"));
	traverse_back(token, cmd, &i);
	traverse_forward(token, cmd, &i);
	resolve_redirects(cmd, &cmd->infile, &cmd->outfile);
}
// NOTE: maybe just open the redirect files after the t_redir* array is created
//		 and if fd < 0 print error message, then either
//		 - continue to execution if we have a valid infile even if other ones where wrong
//		 OR 
//		 - stop execution of that child process if any infile was wrong
//		 (outfiles will be created if they don't exists or stop if they don't have permissions?)
static int	open_redirect_file(t_redirect *redir)
{
	int	fd;

	if (redir->type == INFILE)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == OUTFILE)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

//This feels so hardcoded, probably because It was vibe
int	apply_redirects(t_cmd *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
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
	}
	if (cmd->outfile)
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("minishell");
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	validate_redirs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd->redirect_count)
	{
		if (cmd->redirs[i].type == INFILE)
		{
			fd = open(cmd->redirs[i].filename, O_RDONLY);
			if (fd < 0)
			{
				perror("minishell");
				return (-1);
			}
			close(fd);
		}
		else if (cmd->redirs[i].type == OUTFILE
			|| cmd->redirs[i].type == APPEND)
		{
			fd = open(cmd->redirs[i].filename, O_WRONLY | O_CREAT, 0644);
			if (fd < 0)
			{
				perror("minishell");
				return (-1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}
