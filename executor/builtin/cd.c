/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:33 by manmaria          #+#    #+#             */
/*   Updated: 2026/05/21 16:40:35 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../incs/executor.h"

t_env	*search_for_key(t_shell *sh, char *key)
{
	t_env	*env;

	env = sh->envs;
	while (env && ft_strncmp(env->name, key, keylen(env->name, key)))
		env = env->next;
	if (!env)
		return (NULL);
	return (env);
}

static int	cd_error(char *errmsg, char *path)
{
	ft_printf_fd(2, "minishell: cd: ");
	if (!errmsg && !path)
		ft_printf_fd(2, "too many arguments\n");
	else if (!errmsg)
		ft_printf_fd(2, "%s: No such file or directory\n", path);
	else
		ft_printf_fd(2, "%s %s\n", errmsg, path);
	return (1);
}

static int	change_dir_to_key(t_shell *sh, char *key)
{
	t_env	*env;
	char	*path;
	char	oldpwd[BUFFSIZE];

	getcwd(oldpwd, BUFFSIZE);
	env = search_for_key(sh, key);
	if (!env)
		return (cd_error("variable not set", key));
	path = env->content;
	if (chdir(path) == -1)
		return (cd_error(NULL, path));
	envp_replace_content(search_for_key(sh, "OLDPWD"), oldpwd, CD);
	getcwd(oldpwd, BUFFSIZE);
	envp_replace_content(search_for_key(sh, "PWD"), oldpwd, CD);
	return (0);
}

int	exec_cd(t_shell *sh, t_cmd *cmd)
{
	char	oldpwd[BUFFSIZE];

	if (cmd->args && cmd->args[1] != NULL)
		return (cd_error(NULL, NULL));
	if (!cmd->args || cmd->args[0][0] == '~' || !ft_strcmp("--", cmd->args[0]))
		return (change_dir_to_key(sh, "HOME"));
	else if (cmd->args[0][0] == '-')
		return (change_dir_to_key(sh, "OLDPWD"));
	getcwd(oldpwd, BUFFSIZE);
	if (chdir(cmd->args[0]) == -1)
		return (cd_error(NULL, cmd->args[0]));
	envp_replace_content(search_for_key(sh, "OLDPWD"), oldpwd, CD);
	getcwd(oldpwd, BUFFSIZE);
	envp_replace_content(search_for_key(sh, "PWD"), oldpwd, CD);
	return (0);
}
// WARNING: should I check if funcs() above fail (aka return 1 on malloc error)?
