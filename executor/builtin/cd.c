/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/09 19:01:49 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <linux/limits.h>

// t_token needs to be the list and not tdlist->token
int	exec_cd(t_shell *sh, t_dlist *cmd)
{
	t_token	*token;
	char	oldpwd[ARG_MAX];
	char	path[ARG_MAX];

	token = cmd->next->data;//this is confusing
	path = token->content;
	getcwd(oldpwd, ARG_MAX);
	if (chdir(path) == -1)
		return(/*cd error*/);
	//envp_setvar(update OLDPWD to whats in oldpwd)
	//envp_setvar(update PWD to whats in getcwd)
	return ();
}
