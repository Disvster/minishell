/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TODOcd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/18 21:17:20 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <linux/limits.h>
#include <limits.h>

int	exec_cd(t_shell *sh, t_cmd *cmd)
{
	t_token	*token;
	char	oldpwd[PATH_MAX];
	char	path[PATH_MAX];

	token = cmd->next->data;//this is confusing
	path = token->content;
	getcwd(oldpwd, PATH_MAX);
	if (chdir(path) == -1)
		return(/*cd error*/);
	//envp_setvar(update OLDPWD to whats in oldpwd)
	//envp_setvar(update PWD to whats in getcwd)
	return ();
}

