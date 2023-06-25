/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:58:36 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/06/25 23:32:07 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_not_exist(char *args, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], args) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_env_var(char *args, char **env)
{
	int	i;
	int	overwrite;

	i = 0;
	overwrite = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], args))
		{
			env[i] = args;
			overwrite = 1;
			break ;
		}
		i++;
	}
	if (!overwrite)
		env[i] = args;
}

int	export(char **args, char **env)
{
	int	i;

	if (args[0])
	{
		if (!env_valid(env))
		{
			ft_putstr_fd("export: not a valid identifier: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		if (env_not_exist(args[0], env) == 1)
			add_env_var(args[0], env);
	}
	else
	{
		sort_env(env);
		return (0);
	}
	return (0);
}
