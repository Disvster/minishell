/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:30:18 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/09 23:07:55 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	init_env_list(t_shell	*shl, char	**envp)
{
	t_env	*previous;
	t_env	*temp;
	int		i;

	previous = NULL;
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		temp = malloc(sizeof(t_env));
		if (!temp)
			return (free_envs(shl->envs));
		if (i == 0)
			shl->envs = temp;
		if (previous)
			previous->next = temp;
		if (!fill_env(temp, cp_ename(envp[i]), cp_econt(evnp[i]), true))
			return (free_envs(shl->envs));
		temp->exported = true;
		temp->next = NULL;
		temp->prev = previous;
		previous = temp;
		i++;
	}
	return (1);
}

int	fill_env(t_env	*env, char	*name, char	*cont, bool	exp)
{
	if (!env || !name || !cont)
		return (0);
	env->name = name;
	env->content = cont;
	env->exported = exp;
	return (1);
}

char	*cp_ename(char	*env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i] != '=')
		i++;
	return (ft_substr(env, 0, i - 1));
}

char	*cp_econt(char	*env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env);
	while (env[i] != '=')
		i++;
	if (!env[i + 1])
		return (ft_strdup(""));
	else
		return (ft_substr(env, i + 1, len - i - 1));
}

int	free_envs(t_env	*top)
{
	//WORK IN PROGRESS
}
