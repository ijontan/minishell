/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:58:36 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/16 18:03:39 by itan             ###   ########.fr       */
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

void	add_env_var(char *args, t_sh_data *data)
{
	int		i;
	int		len;
	char	**tmp;

	len = env_len(data->env);
	tmp = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		tmp[i] = data->env[i];
		i++;
	}
	tmp[i] = ft_strdup(args);
	free(data->env);
	data->env = tmp;
}

void	overwrite_var(char *args, t_sh_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		if (ft_strstart(data->env[i], args))
		{
			tmp = data->env[i];
			data->env[i] = ft_strdup(args);
			free(tmp);
			break ;
		}
		i++;
	}
}

int	export(char **args, t_sh_data *data)
{
	int	i;

	i = 1;
	if (args[1])
	{
		while (args[i])
		{
			if (!env_valid(args[i]))
			{
				ft_putstr_fd("export: not a valid identifier: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putchar_fd('\n', 2);
				return (1);
			}
			if (env_not_exist(args[i], data->env))
				add_env_var(args[i], data);
			else
				overwrite_var(args[i], data);
			i++;
		}
	}
	else
		sort_env(data->env);
	return (0);
}
