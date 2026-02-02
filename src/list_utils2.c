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

t_token	*token_get_tail(t_token *n)
{
	if (!n)
		return (NULL);
	while (n->next)
		n = n->next;
	return (n);
}

t_token	*token_get_head(t_token *n)
{
	if (!n)
		return (NULL);
	while (n->prev)
		n = n->prev;
	return (n);
}
