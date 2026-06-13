/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:55:01 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/10 18:12:14 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include "../../../incs/executor.h"

char	*ft_strndup(const char *str, size_t n)
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

bool	export_validate_arg(char *s)
{
	if (!s || !*s)
		return (false);
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	while (*s && *s != '=' && *s != '+')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (false);
		s++;
	}
	if (*s == '+' && *(s + 1) != '=')
		return (false);
	return (true);
}

void	sort_env_array(char **envp, int size)
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

int	export_print_vars(t_shell *sh)
{
	t_env	*curr;
	char	**envp;
	int		i;

	envp = env_list_to_array(sh->envs);
	if (!envp)
		return (ft_printf_fd(2, SH_WAR ERR_MALLOC), 1);
	sort_env_array(envp, envlist_size(sh->envs));
	i = -1;
	while (envp[++i])
	{
		curr = sh->envs;
		ft_printf("declare -x ");
		while (curr && ft_strncmp(curr->name, envp[i],
				keylen(envp[i], curr->name)))
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

int	export_err_invalid_identifier(char *s)
{
	ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", s);
	return (1);
}
