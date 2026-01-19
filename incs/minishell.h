/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:50 by manmaria          #+#    #+#             */
/*   Updated: 2026/01/15 19:40:56 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_manmaria/incs/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "pipex.h"
# include <stdbool.h>

typedef enum type {
    INFILE;
    OUTFILE;
    COMMAND;
    ARG;
    PIPE;
    S_CHAR;
};

typedef struct s_token {
    bool has_quotes;
    char *content;
    t_cmd *command;
    enum type;
    t_token *next;
    t_token *prev;
} t_token;

int	check_sep(char const c, char *sep);
int	find_specials(t_line *line, char **split);

#endif
