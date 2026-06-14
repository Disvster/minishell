# MINISHELL To-do List

## 14/06/26

`alias valmacro='bash valgrind --suppressions=readline.supp --leak-check=full --trace-children=yes --show-leak-kinds=all  --track-origins=yes --tool=memcheck --track-fds=yes ./minishell'`

`alias valmini='bash valgrind --suppressions=readline.supp --trace-children=yes --track-fds=yes ./minishell'`

## 12/06/26

- [ ]  expand ~

## 10/06/26

### STRESS TEST:

- [ ] upon unsetting PATH, program does not work with relative paths
- [ ] also upon unsetting PATH, the response is "command not found" instead of "no such file or directory"

------

- [ ] we are not freeing nothing in child processes executing built-in commands

## 09/06/26

- [ ] maybe remove token_list_clear calls in parsing and let main handle it.
- [ ] incorrect syntax input exit code apparently is 2, review parsing/lexing for this

## 08/06/26
- [X] implemented "working history" (its already preprogrammed in readline)
- [X] HEREDOC COMPLETE

- [ ] we need to get going with exit code definition (on error and not only), may be functions that need to check g_sig to see if they can keep running, others the exit code.

## 02/06/26

- [X] we need to dup the STDIN and STDOUT fd's to `sh->saved_std<in/out>` and restore them always after each command is run, also in exit;
- [ ] find a suitable placement for fd saving and restoring functions (currently in test_main.c);
- [X] still missing heredoc implementation
- [ ] norm:
    - [ ] function sizes
    - [ ] functions per line
- [ ] IMPORTANT check all TODO, NOTE, FIX, WARNING:
    - TODO is self explanatory
    - NOTE is a reminder or an explanation
    - WARNING is either:
        * exit codes of functions that might be wrong or need an error message print
        * or uncertainty if a code line/block will work
    - FIX is things that for sure will not work and need review and re-implementation
    - HACK is code blocks only for debugging
- [ ] implement exit codes;
- [ ] shell shouldn't exit on bad input like unmmatched quotes

## 31/05/26

- [o] signals:
    - [ ] <C-j> is the same as ENTER (currently exits minishell unsafely if no input is given)
    - [X] <C-d> is equal to exit built-in call
    - [X] <C-l> clears screen (is already working for some reason)
    - [ ] pressing ESC repeatedly crashes minishell sometimes? 

- [X] implement working history when pressing up arrow

- [ ] readline prompt with pwd (`$HOME == '~'` if possibe)
    -  check afonso and wallace's build_prompt() function for inspo

- [X] REDIRECTS!!
- [X] HEREDOC  !!

## 28/05/26

need fix here
```sh
[minishell]$ echo $(cat Makefile)
$(t Makefile)
```

## 25/05/26

### EXPORT:

- [ ] `new_env()` can't have `if(!cont)` if we wan't to use it for export, because `cont` might not exist because var isn't exported, it might not always mean malloc error;

- [X] this is now fixed
~when I use the `export` command no args, it is printing these vars:~
```sh
declare -x XDG_SEAT="seat0"
declare -x XDG_SEAT="seat0"
```
~instead of:~
```sh
declare -x XDG_SEAT="seat0"
declare -x XDG_SEAT_PATH="/org/freedesktop/DisplayManager/Seat0"
```
- [X] but now I have a new issue which is I need to know in the `ft_strncmp()`s which string is the one that I'm accurately searching for, e.g.:
    - if str is "ola"
    - and env->name is "olaadeus"
    - then `ft_strncmp(str, env->name, keylen(env->name))`
    - this would give a false positive
```sh
$> export ola=adeus
$> export
declare -x ola="adeus"
$> export olateste=xau
$> export
declare -x ola="adeusxau"
declare -x olateste
```
- fixed by adding the `keylen()` function

## 20/05/26

- [ ] IMPORTANT check all TODO, NOTE, FIX, WARNING:
    - TODO is self explanatory
    - NOTE is a reminder or an explanation
    - WARNING is either:
        * exit codes of functions that might be wrong or need an error message print
        * or uncertainty if a code line/block will work
    - FIX is things that for sure will not work and need review and re-implementation
    - HACK is code blocks only for debugging

    - [ ] fix PIPES >= 4 error message from "'|" to "'||"

## 06/03/26

### Goals for next week

Manel:

- [X] write functions for the built-in commands
    - [X] `cd`
    - [X] `pwd`
    - [X] `echo`
    - [X] `exit`
    - [X] `exit`
    - [X] `env`
    - [X] `export`
    - [X] `unset`
- [X] draft command_exec pipeline:
    - pipes 
    - forks
    - process handling
    - pids
    - [ ] exit status/codes
- [X] study redirecting and heredocs

Festas:

- finish:
- [X] expansion
- [X] appending
- [X] parsing
- [X] olhar para signal handling para ajudar o manelito pretty plssss

## 05/03/26
- [x] Working on expansion
    - Analyzing how bash handles sequences of quotes, of '$' and its different combinations and results.
    - Starting work on an append-based system of running through a string and appending it, expanding when necessary, removing and handling quotes (unless they are inside quotes).
    - Handling special var cases like certain non-alphanumeric characters after expansion of variables.

## 21/02/26
- [x] Setting the types
    - After study, it seems to be mostly done in the following order:
        -First, you set the types of all the meta characters.
        -Then the arguments/commands/files
        -Then you expand
        -Then you set them again. Many people around 42 told me to do this. Still dont understand why exactly

- Regarding the 'expand' approach. Seems fucking incredible, but given the amount of things that can change, maybe its better to work based on strjoin and appends instead of trying to predict the final strlen from the beginning(?)


## 12/02/26
- [X] start the parsing function, namely the "expansion" function that should:
    - remove "quotes" from the final token name
    - expand the variables prefaced by '$' (unless the command is export)
    - when expanding '$' variables, behave differently if there are double-quotes or single quotes
- [X] in parsing, add the function that will define what each token IS (command, pipe, heredoc, arg, etc.)
- [X] expansion may require the types, but may change after expansion. probably will have to set types - expand - set types

## 29/01/26

- [X] finish correcting all the double list functions

Parsing/Lexer:
- [X] create dlist for tokens
- [X] quote handling !!!
- [X] token lenght


## 05/01/26

- [X] Study shell and bash behaviours
    - https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html 
    - https://youtu.be/yTR00r8vBH8?si=YOOw-30E4j5XHpyj
- [X] study built-in commands' behaviours and error management

- [X] how to run a "minishell" program that behaves as if you type "bash"
    - typing both `exit` or `CTR-D` stops the program aka quits the shell
    - signals will be stored in the global variable

- [X] how to handle signals

- [X] understand how to do the parsing and what are concepts like "lexing" or "tokenizing"
- [ ] how to handle the command history

### 1st steps:

1. create a program that prints `[minishell]` and writes what's being typed on the keyboard in front
2. when enter is pressed a line below will appear displaying how the line above was interpreted by the `Lexer`; ex.:
```
[minishell]echo "isto e uma string" > teste.txt
[minishell]cmd:{echo}, args:{isto e uma string}, file:{teste.txt}, spec.chars.:{>}
```
3. separate a built-in command from a outside command:
    a. outside will call execve like pipex
    b. built-ins will be handled by the program
