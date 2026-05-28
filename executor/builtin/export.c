/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:13:56 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/28 16:47:52 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

int	envp_new_var(t_shell *sh, char *str);

static size_t keylen(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] != '=' && s1[i] != '+')
		i++;
	j = 0;
	while (s2[j] && s2[j] != '=' && s2[i] != '+')
		j++;
	if (i >= j)
		return (i);
	return (j);
}

static void	sort_env_array(char **envp, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
				j = i;
			}
			j++;
		}
		i++;
	}
}

static int	export_print_vars(t_shell *sh)
{
	t_env	*curr;
	char	**envp;
	int		i;

	envp = env_list_to_array(sh->envs);
	if (!envp)
		return (1);//TODO: print error? error code? 127?
	sort_env_array(envp, envlist_size(sh->envs));
	i = -1;
	while (envp[++i])
	{
		curr = sh->envs;
		ft_printf("declare -x ");
		while (curr && ft_strncmp(curr->name, envp[i], keylen(envp[i], curr->name)))
			curr = curr->next;
		ft_printf("%s", curr->name);
		if (curr && curr->exported == true && !curr->content)
			ft_printf("=\"\"");
		else if (curr && curr->exported == true)
			ft_printf("=\"%s\"", curr->content);
		ft_printf("\n");
	}
	free_split(envp);
	return (0);
}

bool	export_validate_arg(char *s)
{
	if (!s || !*s)
		return (false);
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	while (*s && *s != '=' && *s != '+')
	{
		if (!ft_isalpha(*s) && *s != '_')
			return (false);
		s++;
	}
	if (*s == '+' && *(s + 1) != '=')
		return (false);
	return (true);
}

static int	export_err_invalid_identifier(char *s)
{
	ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", s);
	return (1);
}

bool	export_check_update(char *s)
{
	char	*tmp;

	tmp = ft_strchr(s, '+');
	if (!tmp || *(tmp + 1) != '=')
		return (false);
	return (true);
}

char	*ft_strndup(const char *str, size_t n)// TODO: move this somewhere maybe lib
{
	char	*dup;
	size_t	i;

	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
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
		return (1);// WARNING: malloc error print?
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
		return (1);// WARNING: malloc error print?
	new_var = new_env(name, NULL, false);
	if (!new_var)
		return (1);
	env_addback(&sh->envs, new_var);
	if (str[i] == 0)
		return (0);// NOTE:env_addback returns 1 on success
	return (export_update_var(sh, str));
}

int	export_replace_content(t_env *env, char *str)
{
	char *replace;
	char *tmp;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (0);
	tmp += 1;
	replace = ft_strdup(tmp);
	if (!replace && tmp)
		return (1);// WARNING: malloc error print?
	if (env->content)
		free(env->content);
	env->content = replace;
	env->exported = true;
	return (0);
}

int	exec_export(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		status;
	char	**arr;
	t_env	*env;

	status = 0;
	if (!cmd->args || !cmd->args[0])
		return (export_print_vars(sh));
	arr = cmd->args;
	i = -1;
	while (arr[++i])
	{
		if (!export_validate_arg(arr[i]))
			status = export_err_invalid_identifier(arr[i]);
		env = sh->envs;
		while (env && ft_strncmp(env->name, arr[i], keylen(arr[i], env->name)))
			env = env->next;
		if (export_check_update(arr[i]) && env)
			status = export_update_var(sh/*env*/, arr[i]);// TODO: change param, don't need to search for matching env in list in this function
		else if (!export_check_update(arr[i]) && env)
			status = export_replace_content(env, arr[i]);
		else// if ((!export_check_update(arr[i]) || export_check_update(arr[i]) && !env))
			status = envp_new_var(sh, arr[i]);
	}
	return (status);
}
