/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/11 17:06:00 by rodmorei         ###   ########.fr       */
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

int		is_builtin(t_token *token);
char	*pipex_strjoin(char *path, char *cmd);
int		search_paths(char **paths, char *cmd, char **test);
int		find_cmd_path(t_cmd *ext, char *cmd, t_env *envlist);
int		create_command(t_cmd **command, t_token **token, t_env *envlist);
int		create_external(t_token *token, t_cmd *ext, t_env *envlist);
int		create_builtin(t_token *token, t_cmd *bi);
t_cmd	*build_command_list(t_token *head, t_env *envs, int *status);

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
void	traverse_back(t_token *token, t_cmd *cmd, int *i);
void	traverse_forward(t_token *token, t_cmd *cmd, int *i);
int		open_infile(char *filename);
int		open_append_or_outfile(char *filename, int type);
int		count_redirects(t_token *token);
void	populate_redirects(t_token *token, t_cmd *cmd);
int		apply_redirects(t_cmd *cmd);

//Executor
int		executor(t_shell *sh);
char	**env_list_to_array(t_env *envs);
int		setup_pipes_and_fork(t_shell *sh, t_cmd *curr, int *pipefd);
int		init_pipeline(t_shell *sh);
int		exec_builtin(t_shell *sh, t_cmd *cmd, bool in_child);
int		exec_pipeline(t_shell *sh, t_cmd *cmds);
void	execve_error(t_shell *shl, t_cmd *command, char	*path);

#endif
