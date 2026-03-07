# Notes related to how minishell will handle external and built-in commmands and this processe's pipeline

### 07/03/26

#### `cd`

- `cd -` same as `pwd`
- `chdir()` in `unistd.h`
- updates the **PWD** and **OLDPWD** env vars

#### `pwd`

- calls `getcwd` and prints the string

#### `echo`

- prints from `stdin` to `stdout`
- `-n` suppresses newlines

#### `exit`

- terminates the shell with an optional exit status
- handles numeric exit status arguments
- cleans up resources
- exits the process with the appropriate status process with the appropriate status

#### `env`

- prints all the environment variables

#### `export`

- adds or updates environment variables
- validates variable names using check export
- only adds (or updates if var name already exists) an env var if export is used with `=`

#### `unset`

- searches and removes environment variables that match the command's argument

### 06/03/26

#### NOTE: 

**Child-safe built-ins** (`echo`, `pwd`, `env`) 
have `in_child == 1` checks, meaning they can execute in child processes during pipelines. 
They only read or display information without modifying shell state.

**Main-process-only built-ins** (`cd`, `export`, `unset`) 
lack the in_child check, so (although they will get executed) they only have a **NOTICEABLE** execution when called directly (not in pipelines). This is because in a pipeline their changes to shell will only take affect in the child process which will be lost after said child dies.

**Special case** (`exit`) handles both contexts - 
it can exit from child processes or the main shell, with different behavior in each case.

#### NOTE: Shell-state changing commands will either:

Change the state of the main process if called individually 
OR 
change the state of the child they're in, not affecting the commands further down the pipeline that depend on the shell's state.


## For a single command:

The command string gets processed by the `check_builtin()` function.

If the command string matches a builtin then it's function is called. 

If not then `check_builtin()` returns 0 and the command string is sent to the `execve()` function.

## For multiple commands separated by Pipes:

The command list gets sent to the `exec_commands()` function which is responsible for:

- forking the **parent** process into has many **child** processes as we have commands;
- iterating through the command list and running it's commands in the previously created children
- all the while sending checking if it is a built-in command or not like for a single command.

## Current Conclusion

NOTE: this conclusion is based only on my current knowledge of command execution which does not include signal handling, redirections and heredocs (+ any other relevant keyword that I might be forgetting).

The difference between individual command execution and a command pipeline is whether the command is run on the main process or on a child process. It appears that shell-changing commands (or "shell-safe") commands don't need special treatment if we unsure that in a pipeline their execution will run in a child process.
