/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:50:33 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/16 20:15:17 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft_manmaria/incs/libft.h"
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		pid;
	char	*path;
	char	**args;
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

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
void	exec_pipe(t_pipex *pipex);
int		get_command(char *cmd_str, char **envp, t_cmd *cmd);
char	*find_cmd_path(char *cmd, char **envp);
char	*pipex_strjoin(char *path, char *cmd);
void	exec_cmd1(t_pipex *pipex);
void	exec_cmd2(t_pipex *pipex);
void	error_exit(t_pipex *pipex, t_cmd *cmd, int exit_code);

#endif
