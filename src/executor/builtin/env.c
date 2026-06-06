/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:44:54 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/19 01:07:44 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int	exec_env(t_shell *sh)
{
	t_env	*temp;

	temp = sh->envs;
	while (temp)
	{
		if (temp->exported)
		{
			ft_printf("%s=", temp->name);
			if (!temp->content)
				ft_printf("");
			else
				ft_printf("%s", temp->content);
			ft_printf("\n");
		}
		temp = temp->next;
	}
	return (0);
}
