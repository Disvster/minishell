/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:40:48 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/10 18:12:05 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

//"[minishell @ ~/Desktop/github/minishell] "
char	*cwd_prompt(t_shell *sh)
{
	char	*home;
	char	buffer[1024];
	char	cwd[1024];

	home = get_env_content(sh->envs, "HOME");
	ft_bzero(buffer, 1024);
	ft_strlcpy(buffer, "[minishell @ ", 1024);
	getcwd(cwd, 1024);
	if (home && ft_strnstr(cwd, home, ft_strlen(home)) == cwd)
	{
		ft_strlcat(buffer, "~", 1024);
		ft_strlcat(buffer, cwd + ft_strlen(home), 1024);
	}
	else
		ft_strlcat(buffer, cwd, 1024);
	ft_strlcat(buffer, "] ", 1024);
	free(home);
	return (ft_strdup(buffer));
}

char	*get_env_content(t_env *head, char *search)
{
	t_env	*curr;
	char	*cont;

	curr = head;
	cont = NULL;
	while (curr && ft_strncmp(curr->name, search, keylen(curr->name, search)))
		curr = curr->next;
	if (!curr || curr->exported == false)
		return (NULL);
	cont = ft_strdup(curr->content);
	if (!cont)
		return (ft_printf_fd(2, SH_ERR ERR_MALLOC), NULL);
	return (cont);
}
