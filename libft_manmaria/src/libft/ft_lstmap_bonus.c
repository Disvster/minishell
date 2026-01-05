/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:32:59 by manmaria          #+#    #+#             */
/*   Updated: 2025/04/17 20:58:06 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapi;
	t_list	*nodi;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	mapi = NULL;
	while (lst)
	{
		nodi = f(lst->content);
		tmp = ft_lstnew(nodi);
		if (!tmp)
		{
			del(nodi);
			ft_lstclear(&mapi, del);
			return (NULL);
		}
		ft_lstadd_back(&mapi, tmp);
		lst = lst->next;
	}
	return (mapi);
}
/*
void	rmv(void *cu)
{
	free(cu);
	cu = NULL;
}

#include <stdio.h>
int	main()
{
	t_list	*c;
	t_list	*dup;
	char	*str = "ola festas";

	c->content = str;
	c->next = 0;
	dup = ft_lstmap(c, (void *)ft_strdup, rmv);
	printf("%s", dup->content);
	free(dup->content);
	free(dup);
	return (0);
}*/
