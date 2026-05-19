/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:39:25 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 18:07:56 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

int	exec_echo(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		nl;
	char	**s;

	nl = 0;
	if (ft_strncmp(cmd->args[0], "-n", 2) == 0)
		nl = 1;
	i = nl;
	s = cmd->args;
	while (s[i])
	{
		ft_printf(s[i]);
		if (s[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nl == 0)
		ft_printf("\n");
	return (1);
}
