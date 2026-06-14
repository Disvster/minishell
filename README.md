*This project has been created as part of the 42 curriculum by manmaria, rodmorei.*

# Minishell

## Description
Minishell is, as the name suggests, a simple shell implementation that attempts to replicate the behaviour of bash in as many parameters as possible. Additionally, it includes the creation of built-in commands such as echo, cd, export and many others. The project works as a way of putting together all the knowledge acquired in previous works (e.g. signal handling in minitalk or pipe handling in pipex) in order to create something palpable and - hopefully - functional.

## Instructions

### Compilation and Execution
To compile minishell, run 'make' in the root directory. If the project compliled correctly, there should be now be an executable called 'minishell' in the directory.

``` bash
make
./minishell
```

### Run Commands
After executing, minishell will prompt you to write what command or action you want to perform. Simply write what you would usually into your bash shell and watch minishell perform the command!

``` bash
minishell> echo I am just a little shell uwu 
minishell> I am just a little shell uwu
```

## Features

- Interactive prompt with readline history
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- External command execution
- Pipes between commands
- Input/output redirections
- Append redirection support
- Heredoc handling
- Environment variable expansion
- `$?` exit status expansion
- Signal handling for interactive use and child processes

## Technical choices

- Split into clear modules for lexing, parsing, expansion, heredoc, redirection, signals, and execution
- Uses custom linked lists for tokens, commands, and environment storage
- Keeps its own shell environment list instead of depending directly on `envp`
- Uses GNU Readline for prompt input and history
- Reuses a custom `libft` and `ft_printf` implementation from the bundled library

## Usage examples

```bash
minishell> echo hello world
hello world
```

```bash
minishell> export NAME=42
minishell> echo $NAME
42
```

```bash
minishell> cat README.md | wc -l
```

```bash
minishell> grep minishell < README.md > output.txt
```

```bash
minishell> cat << EOF
heredoc example
EOF
```

## Project structure

```text
minishell
├── src
│   ├── lexing
│   ├── parsing
│   ├── expansion
│   ├── heredoc
│   ├── redirect
│   ├── executor
│   ├── signal
│   └── shell_utils
├── incs
├── libft_manmaria
└── Makefile
```

## Resources
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - The official documentation for bash, used as a reference for behavior.
- [C Library Understanding](https://www.tutorialspoint.com/c_standard_library) - Half tutorial half manual on understanding c functions. Really useful on understanding the possibilities you have with the permitted functions.
- [Stack Overflow](https://stackoverflow.com) - It's not anything new, but there is nothing better to solve a frustrating problem than finding someone who had the exact problem you had, albeit in a different context, and was helped by a generous cyber-samaritan.

## AI usage
AI was used for optimization, this README, and some debugging.
