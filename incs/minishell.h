/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:50 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/15 19:40:56 by manmaria         ###   ########.fr       */
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

typedef enum {
    INFILE,
    OUTFILE,
    COMMAND,
    ARG,
    PIPE,
    S_CHAR,
} e_type;

typedef struct s_token {
    bool has_quotes;
    char *content;
    t_cmd *command;
    e_type type;
    struct s_token *next;
    struct st_token *prev;
}				t_token;

typedef struct s_dlist
{
	struct s_dlist	*prev;
	void			*data;
	struct s_dlist	*next;

}				t_dlist;

t_dlist	*dlist_new_node(void *content);
t_dlist	*dlist_get_head(t_dlist *n);
t_dlist	*dlist_get_tail(t_dlist *n);
void	dlist_add_first(t_dlist **head, t_dlist *node);
void	dlist_add_last(t_dlist **head, t_dlist *node);
void	fdf_dlist_clear(t_dlist **lst, void (*del)(void *data));

int	check_sep(char const c, char *sep);
int	find_specials(t_line *line, char **split);

#endif
