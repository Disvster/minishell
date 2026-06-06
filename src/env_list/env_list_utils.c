/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:37:23 by rodmorei          #+#    #+#             */
/*   Updated: 2026/05/18 22:42:17 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_env	*new_env(char *name, char *cont, bool exp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		free(name);
		name = NULL;
		free(cont);
		cont = NULL;
		return (NULL);
	}
	if (!name)
		return (free(env), free(cont), NULL);
	// if  (!cont)// FIX:
	// 	return (free(env), free(name), NULL);
	env->next = NULL;
	env->prev = NULL;
	env->name = name;
	env->content = cont;
	env->exported = exp;
	return (env);
}

int	env_addback(t_env **head, t_env	*node)
{
	t_env	*temp;

	temp = *head;
	if (!node)
		return (0);
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	node->prev = temp;
	return (1);
}

int	free_envs(t_env	**head)
{
	t_env	*tmp;
	t_env	*node;

	tmp = NULL;
	node = *head;
	while (node)
	{
		tmp = node->next;
		free(node->content);
		free(node->name);
		if (node)
			free(node);
		node = tmp;
	}
	return (1);
}

int	envlist_size(t_env *head)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
