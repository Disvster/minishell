/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:45:31 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/31 23:33:42 by manmaria         ###   ########.fr       */
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

int	count_redirects(t_token *token)
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

void	populate_redirects(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	traverse_back(token, cmd, &i);
	traverse_forward(token, cmd, &i);
}

void	resolve_redirects(t_cmd *cmd, char **input_file, char **output_file)
{
	int	i;

	*input_file = NULL;
	*output_file = NULL;
	i = 0;
	while (i < cmd->redirect_count)
	{
		if (cmd->redirs[i].type == INFILE)
			*input_file = cmd->redirs[i].filename;
		else if (cmd->redirs[i].type == OUTFILE
			|| cmd->redirs[i].type == APPEND)
			*output_file = cmd->redirs[i].filename;
		i++;
	}
}

// void	*populate_redirect_array(t_token *token, t_cmd *cmd)
// {
// 	int		i;
// 	t_token *tmp;
//
// 	i = 0;
// 	cmd->redirs = ft_calloc(cmd->redirect_count, sizeof(t_redirect));
// 	while (i < cmd->redirect_count)
// 	{
// 		while (tmp && tmp->type != PIPE)
// 		{
// 			if (tmp->type == TFILE)
// 				cmd->redirs[i].filename = tmp->content;// NOTE: CARE OWNERSHIP
// 			if (tmp->prev && cmd->redirs[i].filename
// 				&& (tmp->prev->type == INFILE || tmp->prev->type == OUTFILE
// 					|| tmp->prev->type == APPEND))
// 			{
// 				cmd->redirs[i++].type = tmp->type;
// 				break ;
// 			}
// 			tmp = tmp->prev;
// 		}
// 		tmp = token; 
// 		while (tmp && tmp->type != PIPE)
// 		{
// 			if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPEND)
// 				cmd->redirs[i].type = tmp->type;
// 			if (tmp->type == TFILE)
// 				cmd->redirs[i].filename = tmp->content;// NOTE: CARE OWNERSHIP
// 			tmp = tmp->next;
// 		}
// 	}
// }
