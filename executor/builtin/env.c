/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:44:54 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/22 17:07:26 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// NOTE: printf_fd ?
// NOTE: should ignore arguments ? 
int	exec_env(t_shell *sh)
{
	t_env	*temp;

	temp = sh->envs;
	while (temp)
	{
		if (temp->exported)
			ft_printf("%s=%s\n", temp->name, temp->content);
		temp = temp->next;
	}
	return (0);
}
