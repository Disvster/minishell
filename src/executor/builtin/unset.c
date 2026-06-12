/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:54:47 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/12 22:46:04 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

int	exec_unset(t_shell *sh, t_cmd *cmd)
{
	int		i;
	t_env	*tmp;
	t_env	*save;

	i = -1;
	if (!cmd->args)
		return (0);
	while (cmd->args[++i])
	{
		tmp = sh->envs;
		while (tmp)
		{
			save = tmp->next;
			if (ft_strncmp(tmp->name, cmd->args[i], keylen(cmd->args[i], cmd->args[i])))
			{
				free(tmp->name);
				free(tmp->content);
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				free(tmp);
			}
			tmp = save;
		}
	}
	return (0);
}
