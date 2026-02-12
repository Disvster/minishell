/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:23:34 by rodmorei          #+#    #+#             */
/*   Updated: 2026/02/05 16:36:50 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	char	*rd;
	(void) envp;
	(void)ac;
	(void)av;
	t_dlist *list;

	list = NULL;
	rd = NULL;
	while (1)
	{
		rd = readline("[minishell]");
		list = lexing(rd);
		while (list)
		{
			printf("Token:%s \n", list->data->content);
			list = list->next;
		}
	}
	return (0);
}

