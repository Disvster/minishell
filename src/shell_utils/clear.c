/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:11:46 by manmaria          #+#    #+#             */
/*   Updated: 2026/06/09 16:33:12 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/executor.h"
#include "../../incs/minishell.h"
#include <readline/readline.h>

int	minishell_clear(t_shell *sh, bool close_shell)
{
	if (sh->lineread)
	{
		free(sh->lineread);
		sh->lineread = NULL;
	}
	if (sh->prompt)
	{
		free(sh->prompt);
		sh->prompt = NULL;
	}
	if (sh->tokens)
		tokenlist_clear(&sh->tokens);
	restore_fds(sh);
	if (close_shell == true)
	{
		free_envs(&sh->envs);
		rl_clear_history();
	}
	return (sh->exit_code);
}

void	cleanup_and_exit(int exit_code, t_shell *sh, t_cmd *cmd_list)
{
	cmdlist_clear(&cmd_list);
	minishell_clear(sh, true);
	exit(exit_code);
}
