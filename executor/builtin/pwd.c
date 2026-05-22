/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:39:00 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 18:15:31 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exec_pwd(t_shell *sh)
{
	char	*cwd;

	(void)sh;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf_fd(2, "ERROR: couldn't get current working directory");
		return (0);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
}
