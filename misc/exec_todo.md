# Executor To-do

## 18/05

- [X] export:
    - create new node envp_var
    - append existing variable
- [X] cd:
    - update envp vars OLDPWD and PWD

## 05/05

- [X] command list done
    - [X] token types need to be reviewed
- [X] start command pipeline for command execution
- [X] finish built-in functions

## 28/04

- started building t_cmd list, need to:
    - [X] doublecheck args ownership
    - [X] write the `create_extenal()` function:
        * similar to `create_builtin` but name has to search `envp` for path
        * might be able to create a general function for both of them after name is assigned, saving lines
    - [X] know what tokens are relevant to save in each `t_cmd` node and how/where will I access them
        * which ones are just info for the command VS actually being part of the commands args
    

