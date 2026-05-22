/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:29:43 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/22 20:58:20 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"

static bool	valid_exit_code(const char *s)
{
	int	i;

	if (!s || !*s)
		return (false);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	err_exit(const char *s)
{
	if (!s)
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
	else
	{
		ft_printf_fd(2, "minishell: exit: %s", s);
		ft_printf_fd(2, ": numeric argument required\n");
	}
	return (2);
}

// NOTE: sh->exit_code will receive the return of exec_exit
int	exec_exit(t_shell *sh, t_cmd *cmd)
{
	int		status;
	// t_cmd	*tmp;

	status = 0;
	// tmp = cmd;
	write (1, "exit\n", 5);
	if (cmd->args)
	{
		if (!valid_exit_code(cmd->args[0]))
			sh->exit_code = err_exit(cmd->args[0]);
		else if (cmd->args[1])
			sh->exit_code = err_exit(NULL);
		else
		{
			status = ft_atoi(cmd->args[0]) % 256;
			if (status < 0)
				status += 256;
		}
	}
	// TODO: restore fds?
	cmdlist_clear(&cmd);
	tokenlist_clear(&sh->tokens);
	free_envs(&sh->envs);
	exit(status);
}
