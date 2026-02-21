# MINISHELL To-do List

## 21/02/26
- [x] Setting the types
    - After study, it seems to be mostly done in the following order:
        -First, you set the types of all the meta characters.
        -Then the arguments/commands/files
        -Then you expand
        -Then you set them again. Many people around 42 told me to do this. Still dont understand why exactly

- Regarding the 'expand' approach. Seems fucking incredible, but given the amount of things that can change, maybe its better to work based on strjoin and appends instead of trying to predict the final strlen from the beginning(?)


## 12/02/26
- [ ] start the parsing function, namely the "expansion" function that should:
    - remove "quotes" from the final token name
    - expand the variables prefaced by '$' (unless the command is export)
    - when expanding '$' variables, behave differently if there are double-quotes or single quotes
- [ ] in parsing, add the function that will define what each token IS (command, pipe, heredoc, arg, etc.)
- [ ] expansion may require the types, but may change after expansion. probably will have to set types - expand - set types

## 29/01/26

- [X] finish correcting all the double list functions

Parsing/Lexer:
- [X] create dlist for tokens
- [X] quote handling !!!
- [X] token lenght


## 05/01/26

- [ ] Study shell and bash behaviours
    - https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html 
    - https://youtu.be/yTR00r8vBH8?si=YOOw-30E4j5XHpyj
- [ ] study built-in commands' behaviours and error management

- [X] how to run a "minishell" program that behaves as if you type "bash"
    - typing both `exit` or `CTR-D` stops the program aka quits the shell
    - signals will be stored in the global variable

- [ ] how to handle signals

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
