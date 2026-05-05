/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/04/29 01:40:29 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft_manmaria/incs/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "minishell.h"


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
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		fds[2];
	int		outfile;
	char	**envp;
	char	**argv;
	int		argc;
	int		cmd_count;
}				t_pipex;

int		is_builtin(t_token *token);
char	*pipex_strjoin(char *path, char *cmd);
char	*search_paths(char **paths, char *cmd);
char	*pipex_strjoin(char *path, char *cmd);
int		is_builtin(t_token *token);
t_cmd	*create_external(t_token *token, t_cmd *ext, t_env *envlist);
t_cmd	*create_command(t_token *token, t_env *envlist);
t_cmd	*create_builtin(t_token *token, t_cmd *bi);
t_cmd	*build_command_list(t_token *head, t_env *envs);
// void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
// void	exec_pipe(t_pipex *pipex);
// int		get_command(char *cmd_str, char **envp, t_cmd *cmd);
// char	*find_cmd_path(char *cmd, char **envp);
// char	*pipex_strjoin(char *path, char *cmd);
// void	exec_cmd1(t_pipex *pipex);
// void	exec_cmd2(t_pipex *pipex);
// void	error_exit(t_pipex *pipex, t_cmd *cmd, int exit_code);

#endif
