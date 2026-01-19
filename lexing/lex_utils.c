#include "../incs/minishell.h"
#include "../incs/pipex.h"

int token_len (char *line) {
    int i = 0;

    
}
int skip_wsp(char *line) {
    int i;

    i = 0;
    while (line[i] && (line[i] == 32 || (line[i]  >= 9 &&  line[i]  <= 13)))
        i++;
    return i;
}