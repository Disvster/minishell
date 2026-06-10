/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainWIP.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:06:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/10 18:10:31 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"
#include "incs/executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_sig = 0;// TODO: remove all other g_sig = 0 calls (signals.c ?)

void	save_parent_fds(t_shell *sh)
{
	//NOTE: if redirects && NOT in fork ? 
	//		or always?
	sh->saved_fds[0] = dup(STDIN_FILENO);
	sh->saved_fds[1] = dup(STDOUT_FILENO);
	sh->saved_fds[2] = dup(STDERR_FILENO);
	// else
	// {
	// 	saved[0] = -1;
	// 	saved[1] = -1;
	// 	saved[2] = -1;
	// }
}

void	restore_fds(t_shell *sh)
{
	int	*saved;

	saved = sh->saved_fds;
	if (saved[0] >= 0)
	{
		dup2(saved[0], STDIN_FILENO);
		close(saved[0]);
	}
	if (saved[1] >= 0)
	{
		dup2(saved[1], STDOUT_FILENO);
		close(saved[1]);
	}
	if (saved[2] >= 0)
	{
		dup2(saved[2], STDERR_FILENO);
		close(saved[2]);
	}
}
int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	init_env_list(&sh, envp);
	while (1)
	{
		handle_signal();
		sh.prompt = cwd_prompt(&sh);
		if (!sh.prompt)
			sh.lineread = readline("[minishell] ");
		else
			sh.lineread = readline(sh.prompt);
		save_parent_fds(&sh);
		sh.lineread = readline(cwd_prompt(&sh));
		if (!sh.lineread)
			return (ft_printf("exit\n"), minishell_clear(&sh, true));
		if (sh.lineread[0] != '\0')
			add_history(sh.lineread);
		if (parsing(&sh) != 0)
		{
			minishell_clear(&sh, false);
			continue ;
		}
		if (executor(&sh) != 0)
		{
			sh.exit_code = 1;
			perror("minishell: executor");
		}
		minishell_clear(&sh, false);
	}
	return (0);
}
