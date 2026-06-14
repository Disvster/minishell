/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:29:43 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/12 23:16:41 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/executor.h"
#include "../../../incs/minishell.h"

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

static int	err_exit(const char *s, int *should_exit)
{
	if (!s)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		*should_exit = 0;
		return (2);
	}
	else
	{
		ft_printf_fd(2, "minishell: exit: %s", s);
		ft_printf_fd(2, ": numeric argument required\n");
		*should_exit = 1;
		return (1);
	}
}

// int	exec_exit(t_shell *sh, t_cmd *cmd)
// {
// 	int		status;
//
// 	status = 0;
// 	write (sh->saved_fds[1], "exit\n", 5);
// 	if (cmd->args)
// 	{
// 		if (!valid_exit_code(cmd->args[0]))
// 			status = err_exit(cmd->args[0]);
// 		if (cmd->args[1])
// 			status = err_exit(NULL);
// 		else
// 		{
// 			status = ft_atoi(cmd->args[0]) % 256;
// 			if (status < 0)
// 				status += 256;
// 		}
// 	}
// 	cmdlist_clear(&cmd);
// 	minishell_clear(sh, true);
// 	exit(status);
// }

int	exec_exit(t_shell *sh, t_cmd *cmd)
{
	int	status;
	int	should_exit;

	status = 0;
	should_exit = 1;
	write(2, "exit\n", 5);
	if (cmd->args)
	{
		if (!valid_exit_code(cmd->args[0]))
			status = err_exit(cmd->args[0], &should_exit);
		else if (cmd->args[1])
			status = err_exit(NULL, &should_exit);
		else
			status = ft_atoi(cmd->args[0]) % 256;
	}
	if (status < 0)
		status += 256;
	cmd = cmdlist_get_head(cmd);
	cmdlist_clear(&cmd);
	if (should_exit)
	{
		minishell_clear(sh, true);
		exit(status);
	}
	return (status);
}
