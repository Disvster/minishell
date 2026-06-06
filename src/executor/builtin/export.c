/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:13:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/05 17:02:50 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

int	exec_export(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		status;
	char	**arr;
	t_env	*env;

	status = 0;
	if (!cmd->args || !cmd->args[0])
		return (export_print_vars(sh));
	arr = cmd->args;
	i = -1;
	while (arr[++i])
	{
		if (!export_validate_arg(arr[i]))
			status = export_err_invalid_identifier(arr[i]);
		env = sh->envs;
		while (env && ft_strncmp(env->name, arr[i], keylen(arr[i], env->name)))
			env = env->next;
		if (export_check_update(arr[i]) && env)
			status = export_update_var(sh/*env*/, arr[i]);// TODO: change param, don't need to search for matching env in list in this function
		else if (!export_check_update(arr[i]) && env)
			status = envp_replace_content(env, arr[i], EXPORT);
		else// if ((!export_check_update(arr[i]) || export_check_update(arr[i]) && !env))
			status = envp_new_var(sh, arr[i]);
	}
	return (status);
}
