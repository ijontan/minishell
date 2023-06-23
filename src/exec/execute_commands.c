/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/06/22 16:11:47 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! everything in this file is not tested yet

// static void	setup_pipes(t_sh_data *sh_data, int n)
// {
// 	int	i;

// 	sh_data->pipes = (t_pipe *)ft_calloc(n, sizeof(t_pipe));
// 	i = -1;
// 	while (++i < n - 1)
// 	{
// 		pipe(sh_data->pipes[i].pipe);
// 		sh_data->commands[i].fd_out = sh_data->pipes[i].pipe[1];
// 		sh_data->commands[i + 1].fd_in = sh_data->pipes[i].pipe[0];
// 	}
// }

// static void	close_pipes(t_sh_data *sh_data)
// {
// 	int	i;
// 	int	num_pipes;

// 	num_pipes = 0;
// 	while (sh_data->commands[num_pipes].program)
// 		num_pipes++;
// 	i = -1;
// 	while (++i < num_pipes)
// 	{
// 		close(sh_data->pipes[i].pipe[0]);
// 		close(sh_data->pipes[i].pipe[1]);
// 	}
// 	free(sh_data->pipes);
// }

/**
 * @brief execute a single command
 *
 * @param sh_data contains all data needed to execute commands
 * @param i index of command in sh_data->commands
 * @return pid of child process
 */
// static int	exec_command(t_sh_data *sh_data, int i)
// {
// 	pid_t		pid;
// 	t_command	*cmd;
// 	cmd = &sh_data->commands[i];
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		cmd->program = check_program_exist(cmd->args[0], sh_data->env);
// 		if (cmd->fd_in)
// 			dup2(cmd->fd_in, 0);
// 		else if (i > 0 && !sh_data->commands[i - 1].fd_out)
// 			dup2(sh_data->pipes[i - 1].pipe[1], 0);
// 		if (cmd->fd_out)
// 			dup2(cmd->fd_out, 1);
// 		else if (sh_data->commands[i + 1].fd_in)
// 			dup2(sh_data->pipes[i].pipe[0], 1);
// 		close_pipes(sh_data);
// 		execve(cmd->program, cmd->args, sh_data->env);
// 		perror("minishell");
// 		exit(1);
// 	}
// 	return (pid);
// }

/**
 * @brief execute all command blocks in sh_data->commands
 *
 * @param sh_data contains all data needed to execute commands
 */
void	exec_commands(t_sh_data *sh_data)
{
	(void)sh_data;
	// int	i;
	// int	*pids;
	// i = 0;
	// while (sh_data->commands[i].args)
	// 	i++;
	// setup_pipes(sh_data, i);
	// pids = (int *)ft_calloc(i + 1, sizeof(int));
	// i = -1;
	// while (sh_data->commands[++i].args)
	// 	pids[i] = exec_command(sh_data, i);
	// close_pipes(sh_data);
	// i = -1;
	// while (sh_data->commands[++i].args)
	// 	waitpid(pids[i], NULL, 0);
}
