/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:25:00 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:14 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_sh_data *data)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = cd(args, data);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = pwd();
	if (ft_strcmp(args[0], "env") == 0)
		result = env(args, data->env);
	if (ft_strcmp(args[0], "export") == 0)
		result = export(args, data);
	if (ft_strcmp(args[0], "unset") == 0)
		result = unset(args, data);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		result = exit_buildin(data, args);
		if (data->exited == 1)
			g_sig.sigquit = 1;
	}
	return (result);
}

int	exec_builtin_redirection(t_command *cmd, t_sh_data *data)
{
	int	old_stdout;
	int	old_stdin;
	int	result;

	old_stdout = dup(STDOUT_FILENO);
	old_stdin = dup(STDIN_FILENO);
	sanitize_command_io(cmd, data->env);
	if (cmd->error)
		return (1);
	expand_all_args(cmd, data);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	result = exec_builtin(cmd->args, data);
	dup2(old_stdout, STDOUT_FILENO);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdout);
	close(old_stdin);
	return (result);
}
