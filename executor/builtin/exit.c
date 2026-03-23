/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:29:43 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/23 19:10:06 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// TODO: replace write with ft_printf_fd and possibly err msg with macros
static int	err_exit(const char *s)
{
	if (!s)
		write(2, "minishell: exit: too many arguments\n", 36);
	else
	{
		if (ft_strcmp(s, "--") == 0)
			return (2);
		write(2, "minishell: exit: ", 17);
		write(2, s, ft_strlen(s));
		write(2, ": numeric argument required\n", 28);
	}
	return (2);
}

// NOTE: sh->exit_code will receive the return of exec_exit
int	exec_exit(t_shell *sh, t_token *token)
{
	int		status;
	t_token	*temp;

	status = 0;
	temp = token;
	write (1, "exit\n", 5);
	if (token->next)
	{
		if (!valid_exit_code(token->next->content))
			return (err_exit(token->next->content));
		else if (token->next->next)
			return (err_exit(NULL));
		else
		{
			status = ft_atoi(token->next->content) % 256;
			if (status < 0)
				status += 256;
		}
	}
	return (status);
}
