#include "../incs/minishell.h"
#include "../incs/pipex.h"

t_token * lexer(char *rd_l, t_token **tokens) {
    t_token *token;
    int i;
    int j;

    i = 0;
    j = 0;

    while (rd_l[i]) {
        i += skip_wsp(&rd_l[i]);
        j = token_len(&rd_l[i]);
    }
}