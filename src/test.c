/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:43:27 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/07 18:06:51 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	char	*rd = NULL;
	t_cmd	cmd;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		ft_bzero(&cmd, sizeof(t_cmd));
		rd = readline("[minishell]");
		get_command(rd, envp, &cmd);
		// ft_printf("%s\n", cmd.path);
		int i = 0;
		ft_printf("%s ", cmd.path);
		while (cmd.args[++i])
			ft_printf("%s ", cmd.args[i]);
		ft_printf("\n");
	}
	return (0);
}
