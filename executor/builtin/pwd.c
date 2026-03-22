/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:39:00 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/22 18:49:34 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exec_pwd(t_shell *sh)
{
	char	*cwd;
	t_token	*tmp;

	tmp = sh->tokens;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		// TODO: this needs to be printed in fd = 2
		ft_printf("couldn't get current working directory");
		// or wtv message is more appropriate
		return (1);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
