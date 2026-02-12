/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:50 by manmaria          #+#    #+#             */
/*   Updated: 2026/02/05 16:31:34 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_manmaria/incs/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "pipex.h"
# include <stdbool.h>

typedef enum s_type
{
	INFILE,
	OUTFILE,
	COMMAND,
	ARG,
	PIPE,
	S_CHAR,
}	t_type;

typedef struct s_token
{
	//NOTE: isolated the 4 variables below in a seperate
	//		structure, and in t_dlist have only a pointer to it
	//		to make it easier to clean the list when needed
	bool			has_quotes;
	char			*content;
	t_cmd			*cmd;//NOTE: this var may only exist in
	//				             execve function
	t_type			type;
}				t_token;

typedef struct s_dlist
{
	struct s_dlist	*prev;
	t_token			*data;
	struct s_dlist	*next;

}				t_dlist;

typedef	struct s_env
{
	char	**name;
	char	**content;
	bool	exported;
	struct s_env	*prev;
	struct s_env	*next;
}  t_env;

typedef struct s_shell
{
	char	*lineread;
	t_env	*envs;
	t_dlist *tokens;
} t_shell;

t_dlist	*dlist_new_node(void *data);
t_dlist	*dlist_get_head(t_dlist *n);
t_dlist	*dlist_get_tail(t_dlist *n);
void	dlist_add_first(t_dlist **head, t_dlist *node);
void	dlist_add_last(t_dlist **head, t_dlist *node);
void	dlist_list_clear(t_dlist **lst, void (*del)(void *data));

int		find_specials(t_line *line, char **split);
int		skip_whitespace(char *line);
void	*lexing(char *lineread);
t_token	*tokenizer(char *lineread, int *i);
int		token_length(char *line);
int		is_meta(char ch);
int		exist_quotes (char *line);
t_token	*init_token(char *content);
t_token	*meta_token(char *lineread, int *j);

#endif
