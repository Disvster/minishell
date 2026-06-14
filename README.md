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

## Resources
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - The official documentation for bash, used as a reference for behavior.
- [C Library Understanding](https://www.tutorialspoint.com/c_standard_library) - Half tutorial half manual on understanding c functions. Really useful on understanding the possibilities you have with the permitted functions.
- [Stack Overflow](https://stackoverflow.com) - It's not anything new, but there is nothing better to solve a frustrating problem than finding someone who had the exact problem you had, albeit in a different context, and was helped by a generous cyber-samaritan.

