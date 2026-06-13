/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disaster </var/spool/mail/disaster>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:23:34 by disaster          #+#    #+#             */
/*   Updated: 2026/06/05 17:08:01 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/executor.h"

void	cmdlist_add_first(t_cmd **head, t_cmd *node)
{
	t_cmd	*first;

	if (!*head)
		*head = node;
	else
	{
		first = cmdlist_get_head(*head);
		first->prev = node;
		node->next = first;
	}
}

void	cmdlist_add_last(t_cmd **head, t_cmd *node)
{
	t_cmd	*last;

	if (!*head)
		*head = node;
	else
	{
		last = cmdlist_get_tail(*head);
		last->next = node;
		node->prev = last;
	}
}

t_cmd	*cmdlist_get_tail(t_cmd *n)
{
	if (!n)
		return (NULL);
	while (n->next)
		n = n->next;
	return (n);
}

t_cmd	*cmdlist_get_head(t_cmd *n)
{
	if (!n)
		return (NULL);
	while (n->prev)
		n = n->prev;
	return (n);
}

void	*cmdlist_clear(t_cmd **head)
{
	t_cmd	*temp;
	t_cmd	*node;

	temp = NULL;
	node = *head;
	while (node)
	{
		temp = node->next;
		if (node->is_bi == false && node->path)
			free(node->path);
		if (node->args)
			free(node->args);
		if (node->redirs)
			free(node->redirs);
		node->path = NULL;
		node->args = NULL;
		node->redirs = NULL;
		free(node);
		node = NULL;
		node = temp;
	}
	*head = NULL;
	return (NULL);
}
