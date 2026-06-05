/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/05 17:10:05 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft_manmaria/incs/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include "minishell.h"

# ifndef BUFFSIZE
#  define BUFFSIZE 4096
# endif

# define EXPORT 4
# define CD 5

// TODO: don't need t_line struct
typedef struct s_line
{
	char	**specs;
	bool	spec_count;
	bool	single_q;
	bool	double_q;
}				t_line;

typedef struct s_redirect
{
	t_type	type;
	char	*filename;
	int		heredoc_fd;
}				t_redirect;

typedef struct s_cmd
{
	int				pid;
	char			*path;
	char			**args;
	int				arg_count;
	int				redirect_count;
	bool			is_bi;
	t_redirect		*redirs;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

//list utils
t_cmd	*cmdlist_get_head(t_cmd *n);
t_cmd	*cmdlist_get_tail(t_cmd *n);
void	cmdlist_add_last(t_cmd **head, t_cmd *node);
void	cmdlist_add_first(t_cmd **head, t_cmd *node);
void	*cmdlist_clear(t_cmd **head);

char	**env_list_to_array(t_env *envs);

int		is_builtin(t_token *token);
char	*pipex_strjoin(char *path, char *cmd);
char	*search_paths(char **paths, char *cmd);
char	*find_cmd_path(char *cmd, t_env *envlist);
t_cmd	*create_command(t_token **token, t_env *envlist);
t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist);
t_cmd	*create_builtin(t_token *token, t_cmd *bi);
t_cmd	*build_command_list(t_token *head, t_env *envs);

int		tokenlist_has_commands(t_token *token);

//utils export
int		envp_replace_content(t_env *env, char *str, int bi);
size_t	keylen(char *s1, char *s2);
t_env	*search_for_key(t_shell *sh, char *key);
char	*ft_strndup(const char *str, size_t n);
bool	export_validate_arg(char *s);
int		envp_new_var(t_shell *sh, char *str);
void	sort_env_array(char **envp, int size);
int		export_print_vars(t_shell *sh);
int		export_err_invalid_identifier(char *s);
int		export_update_var(t_shell *sh, char *str);
bool	export_check_update(char *s);

//built-ins
int		exec_cd(t_shell *sh, t_cmd *cmd);
int		exec_echo(t_shell *sh, t_cmd *cmd);
int		exec_env(t_shell *sh);
int		exec_pwd(t_shell *sh);
int		exec_exit(t_shell *sh, t_cmd *cmd);
int		exec_unset(t_shell *sh, t_cmd *cmd);
int		exec_export(t_shell *sh, t_cmd *cmd);

//Redirect
void	populate_redirects(t_token *token, t_cmd *cmd);
int		apply_redirects(t_cmd *cmd);

int		exec_pipeline(t_shell *sh, t_cmd *cmds);

#endif
