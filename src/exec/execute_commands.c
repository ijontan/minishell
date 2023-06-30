/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/06/30 17:00:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipes(t_sh_data *sh_data, t_command_chunk *command_chunk)
{
	t_list		*tmp;
	t_command	*cmd;
	t_command	*next_cmd;
	t_pipe		*pipe_tmp;

	tmp = command_chunk->commands;
	((t_command *)(tmp->content))->fd_in = STDIN_FILENO;
	while (tmp)
	{
		cmd = (t_command *)tmp->content;
		if (tmp->next)
		{
			next_cmd = (t_command *)tmp->next->content;
			pipe_tmp = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
			pipe(pipe_tmp->pipe);
			cmd->fd_out = pipe_tmp->pipe[1];
			next_cmd->fd_in = pipe_tmp->pipe[0];
			ft_lstadd_back(&sh_data->pipes, ft_lstnew(pipe_tmp));
		}
		else
		{
			cmd->fd_out = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
}

static void	close_pipe(void *pipe)
{
	close(((t_pipe *)pipe)->pipe[0]);
	close(((t_pipe *)pipe)->pipe[1]);
}

void	close_pipes(t_sh_data *sh_data)
{
	ft_lstiter(sh_data->pipes, close_pipe);
}

/**
 * @brief execute a single command
 *
 * @param sh_data contains all data needed to execute commands
 * @param i index of command in sh_data->commands
 * @return pid of child process
 */
static pid_t	exec_command(t_sh_data *sh_data, t_command *cmd)
{
	pid_t	pid;

	sanitize_command_io(cmd);
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
		exit(127);
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
	pid_t			*pids;
	t_command_chunk	*chunk;
	t_list			*tmp;

	chunk = (t_command_chunk *)command_chunk->content;
	setup_pipes(sh_data, chunk);
	tmp = chunk->commands;
	pids = (pid_t *)ft_calloc(ft_lstsize(tmp) + 1, sizeof(pid_t));
	tmp = chunk->commands;
	i = 0;
	while (tmp)
	{
		ft_printf("executing command %s\n",
			((t_command *)tmp->content)->args[0]);
		pids[i++] = exec_command(sh_data, (t_command *)tmp->content);
		tmp = tmp->next;
	}
	close_pipes(sh_data);
	i = -1;
	while (pids[++i])
		waitpid(pids[i], NULL, 0);
	free(pids);
}
