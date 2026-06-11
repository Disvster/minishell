/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:02:45 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/05 17:10:15 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

size_t	keylen(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] != '=' && s1[i] != '+')
		i++;
	j = 0;
	while (s2[j] && s2[j] != '=' && s2[j] != '+')
		j++;
	if (i >= j)
		return (i);
	return (j);
}

bool	export_check_update(char *s)
{
	char	*tmp;

	tmp = ft_strchr(s, '+');
	if (!tmp || *(tmp + 1) != '=')
		return (false);
	return (true);
}

int	export_update_var(t_shell *sh, char *str)
{
	char	*add;
	char	*new_content;
	t_env	*env;

	env = sh->envs;
	add = ft_strchr(str, '=');
	if (!add)
		return (1);
	add += 1;
	while (env && ft_strncmp(env->name, str, keylen(env->name, str)))
		env = env->next;
	if (!env)
		return (1);
	if (env->content)
		new_content = ft_strjoin(env->content, add);
	else
		new_content = ft_strdup(add);
	if (!new_content && add)
		return (ft_printf_fd(2, SH_WAR ERR_MALLOC), 1);
	if (env->content)
		free(env->content);
	env->content = new_content;
	env->exported = true;
	return (0);
}

int	envp_new_var(t_shell *sh, char *str)
{
	t_env	*new_var;
	size_t	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i])
		name = ft_strndup(str, i);
	else
		name = ft_strdup(str);
	if (!name)
		return (ft_printf_fd(2, SH_WAR ERR_MALLOC), 1);
	new_var = new_env(name, NULL, false);
	if (!new_var)
		return (ft_printf_fd(2, SH_WAR ERR_MALLOC), 1);
	env_addback(&sh->envs, new_var);
	if (str[i] == 0)
		return (0);// NOTE:env_addback returns 1 on success
	return (export_update_var(sh, str));
}

int	envp_replace_content(t_env *env, char *str, int bi)
{
	char	*replace;
	char	*tmp;

	if (!env)
		return (-1);
	if (bi == EXPORT)
	{
		tmp = ft_strchr(str, '=');
		if (!tmp)
			return (0);
		tmp += 1;
	}
	else
		tmp = str;
	replace = ft_strdup(tmp);
	if (!replace && tmp)
		return (ft_printf_fd(2, SH_WAR ERR_MALLOC), 1);
	if (env->content)
		free(env->content);
	env->content = replace;
	env->exported = true;
	return (0);
}
