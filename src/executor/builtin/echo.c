/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:39:25 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/22 20:51:48 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

static int	check_nl_flag(const char *s)
{
	int	i;

	i = 1;
	if (!s[2])
		return (1);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		if (s[i + 1] == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_echo(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		nl;
	char	**s;

	if (!cmd->args)
		return (ft_printf("\n"), 0);
	(void)sh;
	nl = 0;
	if (cmd->args && ft_strncmp(cmd->args[0], "-n", 2) == 0)
		nl = check_nl_flag(cmd->args[0]);
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
	return (0);
}
