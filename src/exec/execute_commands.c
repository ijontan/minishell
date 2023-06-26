/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/06/26 15:04:32 by itan             ###   ########.fr       */
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
static int	exec_command(t_sh_data *sh_data, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmd->program = check_program_exist(cmd->args[0], sh_data->env);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
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
	while (sh_data->commands[i].args)
		i++;
	setup_pipes(sh_data, i);
	pids = (int *)ft_calloc(i + 1, sizeof(int));
	i = -1;
	while (sh_data->commands[++i].args)
		pids[i] = exec_command(sh_data, i);
	close_pipes(sh_data);
	i = -1;
	while (pid[i])
		waitpid(pids[i++], NULL, 0);
}
