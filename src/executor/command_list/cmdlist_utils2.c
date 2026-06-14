/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:52:44 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/14 20:53:00 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/executor.h"

int	add_empty_command(t_cmd **command, t_cmd **cmds, t_token	*tok)
{
	t_cmd	*temp;

	temp = NULL;
	if (attempt_open(tok) != 0)
		return (1);
	temp = calloc(1, sizeof(t_cmd));
	if (!temp)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC), cmdlist_clear(cmds), 1);
	temp->args = NULL;
	temp->path = NULL;
	temp->redirect_count = -1;
	temp->is_bi = false;
	temp->redirs = NULL;
	cmdlist_add_last(cmds, temp);
	*command = temp;
	return (0);
}
