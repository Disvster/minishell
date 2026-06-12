/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:50 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/10 18:10:00 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_manmaria/incs/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
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

extern int	g_sig;

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
	char		*prompt;
}	t_shell;

// t_dlist	*dlist_new_node(void *data);
// t_dlist	*dlist_get_head(t_dlist *n);
// t_dlist	*dlist_get_tail(t_dlist *n);
// void	dlist_add_first(t_dlist **head, t_dlist *node);
// void	dlist_add_last(t_dlist **head, t_dlist *node);
// void	dlist_list_clear(t_dlist **lst, void (*del)(void *data));

int		skip_whitespace(char *line);
int		lexing(t_token **final, char *lineread, int *err_code);
int		tokenizer(t_token **final, char *lineread, int *i, int *err_code);
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
int		syntax_check(t_shell *shl);
int		pipe_checker(t_token *tok);

// Expansion/Appending
int		expansion(t_token **head, t_shell *shl);
char	*expand(t_token *token, t_shell *shl);//, char	*nstr);
int		append_quoted(t_shell *shl, t_token	*token, char **nstr, int	*i);
int		append_expand(t_shell *shl, t_token *token, char **nstr, int *i);
int		append_letter(char	**nstr, char c, int	*i);
int		append_exit_code(char **nstr, int exit_code, int *i);
void		delete_token(char *str, t_token **tok, t_token **head);
int		is_edge(char c);

// Heredoc
int		read_hdc_quoted(const char	*delimiter, int write_fd, t_shell *sh);
int		read_hdc_unquoted(const char *delimiter, int write_fd, t_shell *sh);
int		write_expanded(int fd, char	*str, t_shell *shl, int *index);
int		read_heredoc_token(t_shell	*sh, t_token	*tok, int *pipefds);
int		handle_heredoc_tokens(t_shell *sh, t_token *tokens);
int		apply_heredoc(int heredoc_fd);

// Signals
void	handle_signal(void);
void	handle_signal_child(void);
void	handle_sigint(int sig);
void	handle_sigpipe(int sig);
void	handle_heredoc_signal(int sig);
void	block_signals(void);

// Env/Export
int		init_env_list(t_shell	*shl, char	**envp);
t_env	*find_env(t_shell *shl, char *env_name);
char	*env_identifier(t_shell *shl, char *to_id, int	*index);
char	*cp_ename(char	*env);
char	*cp_econt(char	*env);
t_env	*new_env(char	*name, char	*cont, bool	exp);
int		env_addback(t_env	**head, t_env	*node);
void	free_envs(t_env	**head);
int		envlist_size(t_env *head);

// General Utils
char	*strjoinfree(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	restore_fds(t_shell *sh);
void	restore_g_sig(t_shell *sh);
int		minishell_clear(t_shell *sh, bool close_shell);
char	*get_env_content(t_env *head, char *search);
char	*cwd_prompt(t_shell *sh);
void	save_parent_fds(t_shell *sh, bool in_fork);

#endif
