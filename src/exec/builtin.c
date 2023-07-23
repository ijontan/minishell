/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:25:00 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/22 00:57:01 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_check(char *command)
{
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
		{
			g_sig.sigquit = 1;
			// free_data(data);
		}
	}
	return (result);
}
