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

#include "../../incs/minishell.h"
#include <readline/readline.h>

int	minishell_clear(t_shell *sh, bool close_shell)
{
	if (sh->lineread)
		free(sh->lineread);
	tokenlist_clear(&sh->tokens);
	restore_fds(sh);
	if (close_shell == true)
	{
		free_envs(&sh->envs);
		rl_clear_history();
		ft_printf("exit\n");
		exit(sh->exit_code);
	}
	return (0);
}
