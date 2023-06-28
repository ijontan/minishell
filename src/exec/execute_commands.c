/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/06/28 16:25:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipes(t_sh_data *sh_data, t_command_chunk *command_chunk)
{
	t_list		*tmp;
	t_command	*cmd;
	t_pipe		*pipe_tmp;

	tmp = command_chunk->commands;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		if (tmp->next)
		{
			pipe_tmp = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
			pipe(pipe_tmp->pipe);
			cmd->fd_out = pipe_tmp->pipe[1];
			cmd->fd_in = pipe_tmp->pipe[0];
			ft_lstadd_back(&sh_data->pipes, ft_lstnew(pipe_tmp));
		}
		else
		{
			cmd->fd_out = STDOUT_FILENO;
			cmd->fd_in = STDIN_FILENO;
		}
		tmp = tmp->next;
	}
}

static void	close_pipe(void *pipe)
{
	close(((t_pipe *)pipe)->pipe[0]);
	close(((t_pipe *)pipe)->pipe[1]);
}

static void	close_pipes(t_sh_data *sh_data)
{
	ft_lstiter(sh_data->pipes, &close_pipe);
}

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
		if (cmd->fd_in == HEREDOC_NUM)
			write(STDIN_FILENO, cmd->heredoc, ft_strlen(cmd->heredoc));
		else
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
void	exec_commands(t_sh_data *sh_data, t_list *command_chunk)
{
	int				i;
	int				*pids;
	t_command_chunk	*chunk;
	t_list			*tmp;

	chunk = (t_command_chunk *)command_chunk->content;
	setup_pipes(sh_data, chunk);
	tmp = chunk->commands;
	i = 0;
	while (tmp++)
		i++;
	pids = (int *)ft_calloc(i + 1, sizeof(int));
	tmp = chunk->commands;
	i = 0;
	while (tmp)
		pids[i++] = exec_command(sh_data, (t_command *)(tmp++)->content);
	close_pipes(sh_data);
	i = -1;
	while (pids[i])
		waitpid(pids[i++], NULL, 0);
	free(pids);
}
