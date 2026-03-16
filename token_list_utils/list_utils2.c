/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:00:25 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/16 16:49:29 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/token_list.h"

t_token	*tokenlist_get_tail(t_token *n)
{
	if (!n)
		return (NULL);
	while (n->next)
		n = n->next;
	return (n);
}

t_token	*tokenlist_get_head(t_token *n)
{
	if (!n)
		return (NULL);
	while (n->prev)
		n = n->prev;
	return (n);
}
