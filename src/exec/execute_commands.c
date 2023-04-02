/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/04/02 22:21:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief execute a single command
 * 
 * @param sh_data contains all data needed to execute commands
 * @param i index of command in sh_data->commands
 * @return pid of child process
 */
static int	exec_command(t_sh_data *sh_data, int i)
{
	pid_t		pid;
	t_command	*cmd;

	cmd = &sh_data->commands[i];
	pid = fork();
	if (pid == 0)
	{
		if (cmd->in_file)
			dup2(cmd->in_fd, 0);
		else if (i > 0 && !sh_data->commands[i - 1].out_file)
			dup2(sh_data->pipes[i - 1]->pipe[1], 0);
		if (cmd->out_file)
			dup2(cmd->out_fd, 1);
		else if (sh_data->commands[i + 1])
			dup2(sh_data->pipes[i]->pipe[0], 1);
		execve(cmd->path, cmd->args, sh_data->env);
		printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		exit(1);
	}
	return (pid);
}

/**
 * @brief execute all command blocks in sh_data->commands 
 * 
 * @param sh_data contains all data needed to execute commands
 */
void	exec_commands(t_sh_data *sh_data)
{
	int	i;
	int	*pids;

	i = 0;
	while (sh_data->commands[i])
		i++;
	pids = (int *)ft_calloc(i + 1, sizeof(int));
	i = -1;
	while (sh_data->commands[++i])
		if (sh_data->commands[i])
			pids[i] = exec_command(sh_data, i);
	i = -1;
	while (sh_data->commands[++i])
		waitpid(pids[i], NULL, 0);
}
