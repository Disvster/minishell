/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disaster </var/spool/mail/disaster>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:24:56 by disaster          #+#    #+#             */
/*   Updated: 2026/05/18 23:39:57 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/executor.h"

static int	command_count(t_cmd *head)
{
	int		count;
	t_cmd	*temp;

	count = 0;
	temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	exec_builtin(t_shell *sh, t_cmd *cmd)
{
	if (ft_strcmp(cmd->path, "echo") == 0)
		return (exec_echo(sh, cmd));
	else if (ft_strcmp(cmd->path, "env") == 0)
		return (exec_env(sh, cmd));
	else if (ft_strcmp(cmd->path, "pwd") == 0)
		return (exec_pwd(sh, cmd));
	else if (ft_strcmp(cmd->path, "exit") == 0)
		return (exec_exit(sh, cmd));
	else if (ft_strcmp(cmd->path, "export") == 0)
		return (exec_export(sh, cmd));
	else if (ft_strcmp(cmd->path, "unset") == 0)
		return (exec_unset(sh, cmd));
	return (1);
}

char	**env_list_to_array(t_env *envs)
{
	char	**envp;
	char	*temp;
	int		count;
	int		i;
	t_env	*tmp;

	count = envlist_size(envs);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = -1;
	tmp = envs;
	while (tmp && ++i < count)
	{
		temp = ft_strjoin(tmp->name, "=");
		if (!temp)
			return (free_split(envp), NULL);
		envp[i] = ft_strjoin(temp, tmp->content);
		free(temp);
		if (!envp[i])
			return (free_split(envp), NULL);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_pipeline_child(t_shell *sh, t_cmd *curr, char **envp, int *pipefd)
{
	
}

void	exec_pipeline_parent(t_shell *sh, t_cmd *curr, int *pipefd, pid_t pid)
{
	
}

int	exec_pipeline(t_shell *sh, t_cmd *cmds)
{
	int		pipefd[2];
	char	**envp;
	t_cmd	*curr;
	pid_t	pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	curr = cmds;
	while (curr && sh->pipeline.count < 1024)
	{
		if (curr->next && pipe(pipefd) < 0)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0) //ERROR
			return (perror("fork"), 1);
		if (pid == 0) //is CHILD
			exec_pipeline_child(sh, curr, envp, pipefd);
		else //is PARENT
			exec_pipeline_parent(sh, curr, pipefd, pid);
		curr = curr->next;
	}
	// waitpid()
	// return( );
}

int	executor(t_shell *sh)
{
	t_cmd	*cmdlist;
	t_cmd	*curr;
	char	**envp;
	int		status;

	cmdlist = build_command_list(sh->tokens, sh->envs);
	if (!cmdlist)// TODO: error mgmnt here
		return (1); // FIX: Error value?
	if (!cmdlist->next && cmdlist->is_bi == true)
		return (status = exec_builtin(sh, cmdlist));
	sh->pipeline.count = 0;
	sh->pipeline.prev_read = -1;
	ft_memset(sh->pipeline.pids, -1, 1024);
	envp = env_list_to_array(sh->envs);// NOTE: should env array init be here?
	if (!envp)
		return (1);// FIX: error value?
	curr = cmdlist;
	while (curr && sh->pipeline.count < 1024)
	{
		if (exec_pipeline(sh, curr, envp) != 0)
			return (1);
		curr = curr->next;
	}
	sh->exit_code = status;
	free_split(envp);

	// OR sh->last_status  = status; ??
	// AND cmd_listclear(&cmdlist); ??
	return (status);
}
