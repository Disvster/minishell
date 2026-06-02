/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:50 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 18:09:25 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_manmaria/incs/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <linux/limits.h>
# include "token_list.h"
// # include "executor.h"
# include "ft_printf_fd.h"

# define READ_END	0
# define WRITE_END	1

typedef struct s_dlist
{
	struct s_dlist	*prev;
	t_token			*data;
	struct s_dlist	*next;

}	t_dlist;

typedef struct s_env
{
	char			*name;
	char			*content;
	bool			exported;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_pipeline
{
    int     prev_read;      // Read end of previous pipe
    pid_t   pids[1024];     // Store all child PIDs
    int     count;          // Number of children forked
}   t_pipeline;

typedef struct s_shell
{
	char		*lineread;
	t_env		*envs;
	t_token		*tokens;
	t_pipeline	pipeline;
	int			exit_code;	
	int			saved_fds[3];
}	t_shell;

// t_dlist	*dlist_new_node(void *data);
// t_dlist	*dlist_get_head(t_dlist *n);
// t_dlist	*dlist_get_tail(t_dlist *n);
// void	dlist_add_first(t_dlist **head, t_dlist *node);
// void	dlist_add_last(t_dlist **head, t_dlist *node);
// void	dlist_list_clear(t_dlist **lst, void (*del)(void *data));

int		skip_whitespace(char *line);
void	*lexing(char *lineread, int *err_code);
t_token	*tokenizer(char *lineread, int *i, int *err_code);
int		token_length(char *line);
int		is_meta(char ch);
int		exist_quotes(char *line);
t_token	*init_token(char *content);
t_token	*meta_token(char *lineread, int *j);
void	free_token_data(void	*token);

// Parsing
int		parsing(t_shell	*shell);
void	set_types(t_token *tlist);
void	set_commands(t_token *tlist);
int		env_len(char *s);
int	syntax_check(t_shell *shl);
int		pipe_checker(t_token *tok);

// Expansion/Appending
int		expansion(t_token *head, t_shell *shl);
char	*expand(t_token *token, t_shell *shl);//, char	*nstr);
int		append_quoted(t_shell *shl, t_token	*token, char **nstr, int	*i);
int		append_expand(t_shell *shl, t_token *token, char **nstr, int *i);
int		append_letter(char	**nstr, char c, int	*i);
int		append_exit_code(char **nstr, int exit_code, int *i);
int		is_edge(char c);

// Env/Export
int		init_env_list(t_shell	*shl, char	**envp);
t_env	*find_env(t_shell *shl, char *env_name);
char	*env_identifier(t_shell *shl, char *to_id, int	*index);
char	*cp_ename(char	*env);
char	*cp_econt(char	*env);
t_env	*new_env(char	*name, char	*cont, bool	exp);
int		env_addback(t_env	**head, t_env	*node);
int		free_envs(t_env	**head);
int		envlist_size(t_env *head);

// General Utils
char	*strjoinfree(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	restore_fds(t_shell *sh);

#endif
