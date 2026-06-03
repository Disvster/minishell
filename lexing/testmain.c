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

int	g_sig;
// TODO: double check if you call this everytime or just when redir is found
void	save_parent_fds(t_shell *sh)
{
	//if redirects && NOT in fork 
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
		save_parent_fds(&sh);

		// TODO: BUILD readline PROMPT
		// t_env *home =  search_for_key(&sh, "HOME");
		// if (!ft_strncmp(curr_path, home->name, keylen(curr_path, home->name)))
		// 	strcpy(curr_path, "~");
		// char prompt[BUFFSIZE] =[minishell @ ]
		// ft_strjoin();
		char curr_path[BUFFSIZE];
		getcwd(curr_path, BUFFSIZE);
		handle_signal();
		sh.lineread = readline("[minishell] ");
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
		int status = exec_pipeline(&sh, cmds);
		sh.exit_code = status;
		cmdlist_clear(&cmds);
		tokenlist_clear(&sh.tokens);
		restore_fds(&sh);

		// TODO: need to follow child processes in GDB to check errors
		// set follow-mode- <child/parent> (?)
		//
		// ENV LIST TESTER:
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
