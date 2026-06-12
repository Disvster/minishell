/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainWIP.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:06:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/12 21:12:40 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/executor.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_sig = 0;

/* 
 *	REPL stands for Read-Eval-Print Loop.
 *
 *	It’s the interactive cycle a shell uses:
 *  1. Read input
 *  2. Evaluate it
 *  3. Print the result
 *  4. Loop back for the next command
*/
static int	repl_loop(t_shell *sh)
{
	while (1)
	{
		handle_signal();
		restore_g_sig(sh);
		sh->prompt = cwd_prompt(sh);
		if (!sh->prompt)
			sh->lineread = readline("[minishell] ");
		else
			sh->lineread = readline(sh->prompt);
		restore_g_sig(sh);
		if (!sh->lineread)
			return (ft_printf("exit\n"), minishell_clear(sh, true), 0);
		if (sh->lineread[0] != '\0')
			add_history(sh->lineread);
		if (parsing(sh) != 0)
		{
			minishell_clear(sh, false);
			continue ;
		}
		executor(sh);
		minishell_clear(sh, false);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	ft_bzero(&sh, sizeof(t_shell));
	save_parent_fds(&sh, false);
	if (init_env_list(&sh, envp) != 0)
		return (1);
	repl_loop(&sh);
	return (0);
}
