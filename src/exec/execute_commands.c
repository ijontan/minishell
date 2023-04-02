/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/04/02 22:33:16 by itan             ###   ########.fr       */
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
		if (cmd->fd_in)
			dup2(cmd->fd_in, 0);
		else if (i > 0 && !sh_data->commands[i - 1].fd_out)
			dup2(sh_data->pipes[i - 1].pipe[1], 0);
		if (cmd->fd_out)
			dup2(cmd->fd_out, 1);
		else if (sh_data->commands[i + 1].fd_in)
			dup2(sh_data->pipes[i].pipe[0], 1);
		execve(cmd->program, cmd->args, sh_data->env);
		perror("minishell");
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
	while (sh_data->commands[i].program)
		i++;
	pids = (int *)ft_calloc(i + 1, sizeof(int));
	i = -1;
	while (sh_data->commands[++i].program)
		pids[i] = exec_command(sh_data, i);
	i = -1;
	while (sh_data->commands[++i].program)
		waitpid(pids[i], NULL, 0);
}
