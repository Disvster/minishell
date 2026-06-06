/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:18:04 by manmaria          #+#    #+#             */
/*   Updated: 2025/07/23 17:53:45 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_nd)
{
	t_list	*last;

	if (!*lst)
		*lst = new_nd;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new_nd;
	}
}
