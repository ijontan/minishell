/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:59:23 by itan              #+#    #+#             */
/*   Updated: 2023/07/24 16:47:52 by itan             ###   ########.fr       */
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
		sanitize_command_io(cmd, sh_data);
		tmp = tmp->next;
	}
}

static void	close_pipe(void *pipe)
{
	t_pipe	*pipe_tmp;

	pipe_tmp = (t_pipe *)pipe;
	close(pipe_tmp->pipe[0]);
	close(pipe_tmp->pipe[1]);
	free(pipe_tmp);
}

bool	not_pipe(t_list *cmd_lst, int *status, t_sh_data *sh_data)
{
	t_list	*tmp;

	tmp = cmd_lst;
	if (tmp)
	{
		if (((t_command *)tmp->content)->error)
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return (true);
		}
		tmp = tmp->next;
	}
	tmp = cmd_lst;
	if (ft_lstsize(tmp) == 1
		&& builtin_check(((t_command *)tmp->content)->args[0]))
	{
		*status = exec_builtin_redirection((t_command *)tmp->content, sh_data);
		return (true);
	}
	return (false);
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

	expand_all_args(cmd->args, sh_data);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		exit(1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (builtin_check(cmd->args[0]))
			exit(exec_builtin_redirection(cmd, sh_data));
		cmd->program = check_program_exist(cmd->args[0], sh_data->env);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		ft_lstclear(&sh_data->pipes, close_pipe);
		if (cmd->program == NULL)
			exit(127);
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
void	exec_commands(t_sh_data *sh_data, t_command_chunk *chunk, int *status)
{
	int		i;
	pid_t	*pids;
	t_list	*tmp;

	tmp = chunk->commands;
	setup_pipes(sh_data, chunk);
	if (not_pipe(tmp, status, sh_data))
		return ;
	pids = (pid_t *)ft_calloc(ft_lstsize(tmp) + 1, sizeof(pid_t));
	i = 0;
	tmp = chunk->commands;
	while (tmp)
	{
		pids[i++] = exec_command(sh_data, (t_command *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&sh_data->pipes, close_pipe);
	i = -1;
	while (pids[++i])
		waitpid(pids[i], status, 0);
	free(pids);
}
