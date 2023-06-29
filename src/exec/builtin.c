/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:25:00 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/06/26 19:28:31 by nwai-kea         ###   ########.fr       */
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
		result = export(args, data->env);
	if (ft_strcmp(args[0], "unset") == 0)
		result = unset(args, data->env);
	return (result);
}
