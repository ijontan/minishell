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

char	*check_quotations(char *args)
{
	int	i;
	int	count;
	int	j;
	char	*tmp;

	i = -1;
	count = 0;
	while (args[++i])
		if (args[i] == '"')
			count++;
	i = 0;
	j = 0;
	if (count % 2 == 0 && count != 0)
	{
		tmp = (char *)ft_calloc(sizeof(char) ,(((int)ft_strlen(args) - count + 1)));
		while (args[i])
		{
			if (args[i] != '"')
			{
				tmp[j] = args[i];
				printf("%c\n", tmp[j]);
				i++;
				j++;
			}
			else
				i++;
		}
		tmp[j] = '\0';
		j = 0;
		return (tmp);
	}
	else
		return (args);
}

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
	int	i;
	int	len;
	char **tmp;

	len = env_len(data->env);
	tmp = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		tmp[i] = data->env[i];
		i++;
	}
	// printf("%s\n", check_quotations(args));
	tmp[i] = ft_strdup(args);
	free(data->env);
	data->env = tmp;
}

void	overwrite_var(char *args, t_sh_data *data)
{
	int	i;
	char	*tmp;

	i = 0;
	// printf("%s\n", check_quotations(args));
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
			// args[i] = check_quotations(args[i]);
			// printf("%s\n", args[i]);
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
