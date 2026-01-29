/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:58:35 by manmaria          #+#    #+#             */
/*   Updated: 2025/12/17 18:45:53 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_dlist	*dlist_new_node(void *content)
{
	t_dlist	*new_node;
	void	*temp;

	new_node = malloc(sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	temp = content;
	// temp->mlx = window->mlx;
	// temp->mlx_win = window->mlx_win;
	// init_img_bonus(temp);
	new_node->prev = NULL;
	new_node->data = temp;
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

//del is bonus_wipe_image
void	fdf_dlist_clear(t_dlist **lst, void (*del)(void *data))
{
	t_dlist	*tmp;
	t_dlist	*node;
	// t_data	*base_ptr;

	if (!lst || !del)
		return ;
	node = *lst;
	if (node->prev)
		node = dlist_get_head(*lst);
	// base_ptr = node->data;
	while (node)
	{
		tmp = node->next;
		del(node->data);
		// if (!tmp)
			// fdf_close_window_bonus(node->window);
		if (node)
			free(node);
		node = tmp;
	}
	// if (base_ptr)
	// 	free(base_ptr);
	// base_ptr = NULL;
	*lst = NULL;
	exit(0);
}
