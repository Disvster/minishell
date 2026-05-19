/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:13:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/19 01:18:09 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

static void	sort_env_array(char **envp, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
				j = i;
			}
			j++;
		}
		i++;
	}
}

static int	print_export_vars(t_shell *sh)
{
	t_env	*curr;
	char	**envp;
	int		i;
	
	envp = env_list_to_array(sh->envs);
	if (!envp)
		return (1);//TODO: print error? error code?
	sort_env_array(envp, envlist_size(sh->envs));
	i = -1;
	while (envp[++i])
	{
		curr = sh->envs;
		ft_printf("declare -x ");
		while (curr && ft_strcmp(envp[i], curr->name))
			curr = curr->next;
		ft_printf("%s", curr->name);
		if (curr->exported == true && !curr->content)
			ft_printf("=\"\"");
		else if (curr->exported == true)
			ft_printf("=\"%s\"", curr->content);
		ft_printf("\n");
	}
	return (0);
}

int	update_env_list(t_shell *shell, t_cmd *cmd)
{
	
}

int	exec_export(t_shell *sh, t_cmd *cmd)
{
	if (!cmd->args)
		return (print_export_vars(sh));
	if (cmd->args)
		return (update_env_list(sh, cmd));
}
