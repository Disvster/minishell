/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disaster </var/spool/mail/disaster>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:23:34 by disaster          #+#    #+#             */
/*   Updated: 2026/05/05 19:38:32 by disaster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"

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
	int		i;

	temp = NULL;
	node = *head;
	i = -1;
	while (node)
	{
		temp = node->next;
		if (node->is_bi == false && node->path)
		{
			free(node->path);
			node->path = NULL;
		}
		if (node->args)
		{
			// WARNING: node->args is a pointer array 
			// where each variable in the array points to 
			//	(1 or more)token->content(s)
			while (node->args[++i])
			{
				free(node->args[i]);
				node->args[i] = NULL;
			}
		}
		free(node);
		node = temp;
	}
	return (NULL);
}
