This project has been created as part of the 42 curriculum by [manmaria](intra.42.fr/users/manmaria) and [rodmorei](intra.42.fr/users/rodmorei).*

# Minishell

## Description

Minishell is, as the name suggests, a simple shell implementation that attempts to replicate the behaviour of bash in as many parameters as possible. 

Additionally, it includes the creation of built-in commands such as echo, cd, export and many others present in the "Features" section of this README. 

The project works as a way of putting together all the knowledge acquired in previous works (e.g. signal handling in minitalk or pipe handling in pipex) in order to create something palpable and - hopefully - functional.

## Instructions

### Compilation and Execution

To compile minishell, run 'make' in the root directory. If the project compiled correctly, there should now be an executable called 'minishell' in the directory.

``` bash
$> make

======  MINISHELL ======
Compilation complete! minishell file generated. 

$> ./minishell
[minishell @ ~/Projects/minishell]
```

### Run Commands
After executing, minishell will prompt you to write what command or action you want to perform. Simply write what you would usually into your bash shell and watch minishell go.


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

- Split into clear modules for lexing, parsing, expansion, heredoc, redirection, signals, and command execution
- Uses custom linked lists for tokens, commands, and environment storage
- Keeps its own shell environment list instead of depending directly on `envp`
- Heredoc handling as fd buffers using pipe()

## Usage examples

```bash
[minishell @ ~/Projects/minishell] echo hello world
hello world
```

```bash
[minishell @ ~/Projects/minishell] export NAME=42
[minishell @ ~/Projects/minishell] echo $NAME
42
```

```bash
[minishell @ ~/Projects/minishell] cat README.md | wc -l
109
```

```bash
[minishell @ ~/Projects/minishell] grep minishell < README.md > output.txt
```

```bash
[minishell @ ~/Projects/minishell] cat << EOF
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
├── libft
└── Makefile
```

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - The official documentation for **bash**, used as a reference for behavior;

- [C Library Understanding](https://www.tutorialspoint.com/c_standard_library) - Half tutorial half manual on understanding **c** functions. Really useful to figure out the possibilities you have with the permitted functions;

- [Stack Overflow](https://stackoverflow.com) - It's not anything new, but there is nothing better to solve a frustrating problem than finding someone who had the exact problem you had, albeit in a different context, and then was helped by a generous cyber-samaritan.

## AI usage

AI was used during the making of this project for things like brainstorming code architecture, analyzing bash behaviours, sanitation checks, this README and in general on the many helpful tools used when debugging.
