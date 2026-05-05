/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:58:35 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/05 19:36:14 by disaster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include "../incs/token_list.h"

t_token	*tokenlist_new_node(void *content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = (char *)content;
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

void	tokenlist_clear(t_token **lst)
{
	t_token	*tmp;
	t_token	*node;

	tmp = NULL;
	node = *lst;
	while (node)
	{
		tmp = node->next;
		free(node->content);
		// if (node->cmd)
		// 	free(node->cmd);
		if (node)
			free(node);
		node = tmp;
	}
}
