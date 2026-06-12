/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:13:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/12 21:21:35 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

int	exec_export(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		status;
	t_env	*env;

	status = 0;
	if (!cmd->args || !cmd->args[0])
		return (export_print_vars(sh));
	i = -1;
	while (cmd->args[++i])
	{
		if (!export_validate_arg(cmd->args[i]))
		{
			status = export_err_invalid_identifier(cmd->args[i]);
			continue ;
		}
		env = sh->envs;
		while (env && ft_strncmp(env->name, cmd->args[i], keylen(cmd->args[i], env->name)))
			env = env->next;
		if (export_check_update(cmd->args[i]) && env)
			status = export_update_var(sh, cmd->args[i]);
		else if (!export_check_update(cmd->args[i]) && env)
			status = envp_replace_content(env, cmd->args[i], EXPORT);
		else
			status = envp_new_var(sh, cmd->args[i]);
	}
	return (status);
}
// NOTE: line 40: else if
// ((!export_check_update(cmd->args[i]) || export_check_update(cmd->args[i]) && !env))
