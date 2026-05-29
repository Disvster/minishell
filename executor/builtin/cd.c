/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/21 16:40:35 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

int	exec_cd(t_shell *sh, t_cmd *cmd)
{
	(void)sh;
	(void)cmd;
	return (-1);
}

// int	exec_cd(t_shell *sh, t_cmd *cmd)
// {
// 	char	*oldpwd;
//
// 	if (cd->args && cd->args[1] != NULL)
// 		return (cd_too_many_args());
// 	if (!cmd->args || cmd->args[0][0] == '~' || !ft_strcmp("--", cmd->args[0]))
// 		return (change_dir_to_key(sh, "HOME"));
// 	else if (cmd->args[0][0] == '-')
// 		return (change_dir_to_key(sh, "OLDPWD"));
// 	oldpwd = getcwd(NULL, 0);
// 	export_replace_content(search_for_key(sh, "OLDPWD"), oldpwd);
// 	free(oldpwd);
// 	if (chdir(cmd->args[0]) == -1)
// 		return (cd_error(NULL, path), 1);
// 	return (0);
// }
