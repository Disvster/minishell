/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:30:18 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/11 19:06:19 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

int	init_env_list(t_shell	*shl, char	**envp)
{
	t_env	*head;
	t_env	*temp;
	int		i;

	head = NULL;
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		temp = new_env(cp_ename(envp[i]), cp_econt(envp[i]), true);
		if (!temp)
			return (free_envs(&head));
		if (!head)
			head = temp;
		else
			env_addback(&head, temp);
		i++;
	}
	shl->envs = head;
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
