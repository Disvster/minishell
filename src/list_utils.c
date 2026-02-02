/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:58:35 by manmaria          #+#    #+#             */
/*   Updated: 2026/02/02 17:31:27 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_dlist	*dlist_new_node(void *content)
{
	t_dlist *new_node;

	new_node = malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->data = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	dlist_add_first(t_dlist **head, t_dlist *node)
{
	t_dlist	*first;

	if (!*head)
		*head = node;
	else
	{
		first = dlist_get_head(*head);
		first->prev = node;
		node->next = first;
	}
}

void	dlist_add_last(t_dlist **head, t_dlist *node)
{
	t_dlist	*last;

	if (!*head)
		*head = node;
	else
	{
		last = dlist_get_tail(*head);
		last->next = node;
		node->prev = last;
	}
}

void	dlist_list_clear(t_dlist **lst, void (*del)(void *data))
{
	t_dlist	*tmp;
	t_dlist	*node;
	t_token	*base_ptr;

	if (!lst || !del)
		return ;
	node = *lst;
	if (node->prev)
		node = dlist_get_head(*lst);
	base_ptr = node->data;
	while (node)
	{
		tmp = node->next;
		del(node->data);
		if (node)
			free(node);
		node = tmp;
	}
	if (base_ptr)
		free(base_ptr);
	base_ptr = NULL;
	*lst = NULL;
}
