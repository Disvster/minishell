/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:54:47 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/22 19:22:35 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exec_unset(t_shell *sh, char *content)
{
	t_env	*tmp;

	tmp = sh->envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, content) == 0)
		{
			free(tmp->name);
			free(tmp->content);
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
			return (1);
		}
	}
	return (0); // no unset var was found, return 0
}
