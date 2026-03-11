/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodmorei <rodmorei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:45:38 by rodmorei          #+#    #+#             */
/*   Updated: 2026/03/05 18:00:47 by rodmorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/minishell.h"

char	*env_identifier(t_shell *shl, char *to_id, int	*index)
{
	int		size;
	int		i;
	char	*env_name;
	t_env	*variable;

	i = *index;
	env_name = NULL;
	variable = NULL;
	size = 0;
	while (to_id[i] && (ft_isalnum(to_id[i]) || to_id[i] == '_'))
	{
		size++;
		i++;
	}
	env_name = ft_substr(to_id, i, size);
	variable = find_env(shl, env_name);
	if (variable)
		return (free(env_name), ft_strdup(variable->content));
	else
		return (ft_strdup(""));
}

t_env	*find_env(t_shell *shl, char *env_name)
{
	t_env	*temp;

	temp = shl->envs;
	while (temp)
	{
		if (ft_strcmp(temp->name, env_name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	is_edge(char c)
{
	return (c == '!' || c == '#' || c == '$' || c == '*' || c == '@'
		|| c == '-');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*strjoinfree(char *s1, char *s2)
{
	size_t	i;
	size_t	ltotal;
	char	*scat;

	if (!s1)
		return (0);
	ltotal = ft_strlen(s1) + ft_strlen(s2);
	scat = (char *)malloc(sizeof(char) * (ltotal + 1));
	if (!scat)
		return (free (s1), NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		scat[i] = s1[i];
		i++;
	}
	while (i < ltotal)
	{
		scat[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	scat[i] = '\0';
	return (free (s1), scat);
}
