/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 23:40:10 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft_manmaria/incs/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>


typedef struct s_line
{
	char	**specs;
	bool	spec_count;
	bool	single_q;
	bool	double_q;
}				t_line;

typedef struct s_cmd
{
	int				pid;
	char			*path;
	char			**args;
	int				arg_count;
	int				redirect_count;
	bool			is_bi;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

# include "minishell.h"

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
t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist);
t_cmd	*create_command(t_token *token, t_env *envlist);
t_cmd	*create_builtin(t_token *token, t_cmd *bi);
t_cmd	*build_command_list(t_token *head, t_env *envs);

//built-ins
int	exec_echo(t_shell *sh, t_cmd *cmd);
int	exec_env(t_shell *sh);
int	exec_pwd(t_shell *sh);
int	exec_exit(t_shell *sh, t_cmd *cmd);
int	exec_unset(t_shell *sh, t_cmd *cmd);

#endif
