/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:30:19 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/16 16:47:01 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "pipex.h"

typedef enum s_type
{
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
	COMMAND,
	ARG,
	TFILE,
	FLAG,
	PIPE,
	S_CHAR,
	LIMITER,
}	t_type;

typedef struct s_token
{
	struct s_token	*prev;

	bool			has_quotes;
	char			*content;
	t_cmd			*cmd;
	t_type			type;

	struct s_token	*next;
}				t_token;

t_token	*tokenlist_new_node(void *data);
t_token	*tokenlist_get_head(t_token *n);
t_token	*tokenlist_get_tail(t_token *n);
void	tokenlist_add_first(t_token **head, t_token *node);
void	tokenlist_add_last(t_token **head, t_token *node);
// void	tokenlist_list_clear(t_token **lst, void (*del)(void *data));

#endif
