/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:58:35 by manmaria          #+#    #+#             */
/*   Updated: 2026/03/16 16:49:17 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/token_list.h"

t_token	*tokenlist_new_node(void *content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	tokenlist_add_first(t_token **head, t_token *node)
{
	t_token	*first;

	if (!*head)
		*head = node;
	else
	{
		first = tokenlist_get_head(*head);
		first->prev = node;
		node->next = first;
	}
}

void	tokenlist_add_last(t_token **head, t_token *node)
{
	t_token	*last;

	if (!*head)
		*head = node;
	else
	{
		last = tokenlist_get_tail(*head);
		last->next = node;
		node->prev = last;
	}
}

// TODO: refactor this function
void	tokenlist_list_clear(t_token **lst, void (*del)(void *data))
{
	t_token	*tmp;
	t_token	*node;
	t_token	*base_ptr;

	if (!lst || !del)
		return ;
	node = *lst;
	if (node->prev)
		node = tokenlist_get_head(*lst);
	// base_ptr = node->data;
	while (node)
	{
		tmp = node->next;
		// del(node->data);
		if (node)
			free(node);
		node = tmp;
	}
	if (base_ptr)
		free(base_ptr);
	base_ptr = NULL;
	*lst = NULL;
}
