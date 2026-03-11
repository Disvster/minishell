/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:23:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/11 20:47:36 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_shell	*shl;
	t_dlist	*tok;

	(void)ac;
	(void)av;
	tok = NULL;
	shl = malloc(sizeof(t_shell));
	init_env_list(shl, envp);
	while (1)
	{
		shl->lineread = readline("[minishell]");
		parsing(shl);
		tok = shl->tokens;
		while (tok)
		{
			printf("Token:%s \n", tok->data->content);
			tok = tok->next;
		}
	}
	return (0);
}
