# Executor To-do

## 28/04

- started building t_cmd list, need to:
    - [ ] doublecheck args ownership
    - [ ] write the `create_extenal()` function:
        * similar to `create_builtin` but name has to search `envp` for path
        * might be able to create a general function for both of them after name is assigned, saving lines
    - [ ] know what tokens are relevant to save in each `t_cmd` node and how/where will I access them
        * which ones are just info for the command VS actually being part of the commands args
    
- [ ] finish built-in functions

