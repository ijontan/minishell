/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:58:36 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/23 01:34:25 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_not_exist(char *args, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstart(env[i], args))
			return (0);
		i++;
	}
	return (1);
}

void	add_env_var(char *args, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strstart(env[i], args))
		{
			env[i] = args;
			break ;
		}
		i++;
	}
}

void	overwrite_var(char *args, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstart(env[i], args))
		{
			env[i] = args;
			break ;
		}
		i++;
	}
}

int	export(char **args, char **env)
{
	if (args[1])
	{
		if (!env_valid(args[1]))
		{
			ft_putstr_fd("export: not a valid identifier: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putchar_fd('\n', 2);
			return (1);
		}
		if (env_not_exist(args[1], env))
			add_env_var(args[1], env);
		else
			overwrite_var(args[1], env);
	}
	else
		sort_env(env);
	return (0);
}
