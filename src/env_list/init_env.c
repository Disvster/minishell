/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:30:18 by rodmorei          #+#    #+#             */
/*   Updated: 2026/05/05 19:38:25 by disaster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
			return (free_envs(&head), 1);
		if (!head)
			head = temp;
		else
			env_addback(&head, temp);
		if (!temp->content)
			return (free_envs(&head), 1);
		i++;
	}
	shl->envs = head;
	return (0);
}

char	*cp_ename(char	*env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

char	*cp_econt(char	*env)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(env);
	str = NULL;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		str = ft_strdup("");
	else if (!env[i + 1])
		str = ft_strdup("");
	else
		str = ft_substr(env, i + 1, len - i - 1);
	if (!str)
		return (NULL);
	return (str);
}

int	shell_lvl_change(t_shell *shl, int lvl_change)
{
	int		new_lvl;
	char	*temp;
	t_env	*temp_env;

	temp = NULL;
	new_lvl = 0;
	temp_env = find_env(shl, "SHLVL");
	if (!temp_env)
		return (shl->exit_code = 1,
			ft_printf_fd(2, "ERROR : SHLVL not found\n"), 2);
	new_lvl = ft_atoi(temp_env->content) + lvl_change;
	if (new_lvl > 999)
		return (temp_env->content = "1",
			ft_printf_fd(2, "warning : SHLVL too high, resetting to 1\n")
			, 2);
	temp = ft_itoa(new_lvl);
	if (!temp)
		return (shl->exit_code = 1, ft_printf_fd(2, ERR_MALLOC), 2);
	if (temp_env->content)
		free (temp_env->content);
	temp_env->content = temp;
	return (0);
}
