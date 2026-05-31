/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:23:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/05/25 23:19:49 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;
	// t_env	*env;
	t_token	*tok;

	(void)ac;
	(void)av;
	tok = NULL;
	// shl = malloc(sizeof(t_shell));
	// shl.exit_code = 0;
	init_env_list(&sh, envp);
	// env = NULL;
	// env = shl.envs;
	while (1)
	{
		// TODO: BUILD readline PROMPT
		// t_env *home =  search_for_key(&sh, "HOME");
		// if (!ft_strncmp(curr_path, home->name, keylen(curr_path, home->name)))
		// 	strcpy(curr_path, "~");
		// char prompt[BUFFSIZE] =[minishell @ ]
		// ft_strjoin();
		char curr_path[BUFFSIZE];
		getcwd(curr_path, BUFFSIZE);
		sh.lineread = readline("[minishell]$ ");
		parsing(&sh);
		tok = sh.tokens;
		if (!tok)
			return (1);
		// while (tok)
		// {
		// 	printf("Token:%s \n", tok->content);
		// 	//TYPE CHECK:
		// 	//printf("Token Type :%d \n", tok->type);
		// 	tok = tok->next;
		// }
		t_cmd *cmds = build_command_list(sh.tokens, sh.envs);

		// TODO: need to follow child processes in GDB to check errors
		// set follow-mode- <child/parent> (?)
		int status = exec_pipeline(&sh, cmds);
		sh.exit_code = status;
		cmdlist_clear(&cmds);
		tokenlist_clear(&sh.tokens);
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
