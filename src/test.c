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
	(void)ac;
	(void)av;
	while (1)
	{
		readline("[minishell]");
		// ft_printf("%s\n", rd);
	}
}
