/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:04:10 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/22 22:00:11 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char *args, t_sh_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = (char **)ft_calloc(env_len(data->env) + 1, sizeof(char *));
	while (data->env[i])
	{
		// printf("%s\n", data->env[i]);
		if (ft_strstart(args, data->env[i]))
			i++;
		if (data->env[i])
		{
			tmp[j++] = ft_strdup(data->env[i]);
			i++;
		}
	}
	tmp[j] = '\0';
	free_2d(data->env);
	data->env = tmp;
}

static void	remove_env_no_equal(char *args, t_sh_data *data)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = (char **)ft_calloc(env_len(data->env) + 1, sizeof(char *));
	while (data->env[i])
	{
		if (ft_strcmp(args, data->env[i]) == 0)
			i++;
		if (data->env[i])
		{
			tmp[j++] = ft_strdup(data->env[i]);
			i++;
		}
	}
	tmp[j] = '\0';
	free_2d(data->env);
	data->env = tmp;
}

int	print_error(void)
{
	ft_putstr_fd("unset: Too few arguments.", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	unset(char **args, t_sh_data *data)
{
	int	i;
	int	pos;

	if (!args[1])
		return (print_error());
	i = 0;
	while (args[++i])
	{
		pos = find_env_pos(args[i], data->env);
		if (data->env[pos])
		{
			if (ft_hasequal(data->env[pos]))
				remove_env(args[i], data);
			else
				remove_env_no_equal(args[i], data);
		}
	}
	return (1);
}
