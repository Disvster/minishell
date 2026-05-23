/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:23:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/05/22 21:10:57 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_shell	shl;
	// t_env	*env;
	t_token	*tok;

	(void)ac;
	(void)av;
	tok = NULL;
	// shl = malloc(sizeof(t_shell));
	// shl.exit_code = 0;
	init_env_list(&shl, envp);
	// env = NULL;
	// env = shl.envs;
	while (1)
	{
		shl.lineread = readline("[minishell]$ ");
		parsing(&shl);
		tok = shl.tokens;
		if (!tok)
			return (1);
		// while (tok)
		// {
		// 	printf("Token:%s \n", tok->content);
		// 	//TYPE CHECK:
		// 	//printf("Token Type :%d \n", tok->type);
		// 	tok = tok->next;
		// }

		t_cmd *cmds = build_command_list(shl.tokens, shl.envs);
		int status = exec_pipeline(&shl, cmds);
		shl.exit_code = status;
		cmdlist_clear(&cmds);
		tokenlist_clear(&shl.tokens);
		// // ENV LIST TESTER:
		// while (env)
		// {
		// 	printf("Env Name:%s \n", env->name);
		// 	printf("Env Content: %s \n", env->content);
		// 	env = env->next;
		// }

		// ENV cmd test
		// exec_env(shl);
	}
	return (0);
}
