/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:00:25 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/17 18:45:49 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_dlist	*dlist_get_tail(t_dlist *n)
{
	if (!n)
		return (NULL);
	while (n->next)
		n = n->next;
	return (n);
}

t_dlist	*dlist_get_head(t_dlist *n)
{
	if (!n)
		return (NULL);
	while (n->prev)
		n = n->prev;
	return (n);
}
