# MINISHELL To-do List
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"' ) && quote == 0)
			quote = line[i];
		else if (line[i] == quote)

		i++;
	}
	return (i);

## 29/01/26

- [ ] finish correcting all the double list functions

Parsing/Lexer:
- [ ] create dlist for tokens
- [ ] quote handling !!!
- [ ] token lenght


## 05/01/26

- [ ] Study shell and bash behaviours
    - https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html 
    - https://youtu.be/yTR00r8vBH8?si=YOOw-30E4j5XHpyj
- [ ] study built-in commands' behaviours and error management

- [ ] how to run a "minishell" program that behaves as if you type "bash"
    - typing both `exit` or `CTR-D` stops the program aka quits the shell
    - signals will be stored in the global variable

- [ ] how to handle signals

- [ ] understand how to do the parsing and what are concepts like "lexing" or "tokenizing"
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
