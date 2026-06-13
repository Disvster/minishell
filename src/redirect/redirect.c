/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:45:31 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/10 16:43:19 by manmaria         ###   ########.fr       */
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

#include "../../incs/executor.h"

void	populate_redirects(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->redirect_count = count_redirects(token);
	if (cmd->redirect_count == 0)
		return ;
	cmd->redirs = ft_calloc(cmd->redirect_count, sizeof(t_redirect));
	if (!cmd->redirs)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC));
	traverse_back(token, cmd, &i);
	traverse_forward(token, cmd, &i);
}

int	apply_redirects(t_cmd *cmd)
{
	int		i;
	t_type	type;

	i = 0;
	while (i < cmd->redirect_count)
	{
		type = cmd->redirs[i].type;
		if (type == HEREDOC)
			if (apply_heredoc(cmd->redirs[i].heredoc_fd) < 0)
				return (-1);
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

int	attempt_open(t_token	*token)
{
	int	fd;
	char	*filename;

	filename = NULL;
	while (token)
	{
		fd = 0;
		if (token->next && token->next->type == TFILE)
		{
			if (token->next)
				filename = token->next->content;
			if (token->type == INFILE)
				fd = open(filename, O_RDONLY);
			else if (token->type == OUTFILE)
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (token->type == APPEND)
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (ft_printf_fd(2, "minishell: "), perror(filename), 1);
		}
		token = token->next;
	}
	return (0);
}
