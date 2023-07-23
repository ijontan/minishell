/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:04:10 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/14 15:50:36 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char *args, t_sh_data *data)
{
	// int	i;
	// int	count;

	// free(env[pos]);
	// env[pos] = NULL;
	// i = pos;
	// count = pos + 1;
	// while (env[i + 1])
	// {
	// 	env[i] = ft_strdup(env[i + 1]);
	// 	free(env[i + 1]);
	// 	i++;
	// 	count++;
	// }
	int	i;
	int	j;
	int	len;
	char **tmp;

	len = env_len(data->env);
	tmp = (char **)ft_calloc(len, sizeof(char *));
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (!ft_strstart(args, data->env[i]))
			tmp[j++] = data->env[i];
		else
			free(data->env[i]);
		i++;
	}
	free(data->env);
	data->env = tmp;
}

int	unset(char **args, t_sh_data *data)
{
	int	i;
	int	pos;

	if (!args[1])
	{
		ft_printf("unset: Too few arguments.\n");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		pos = find_env_pos(args[i], data->env);
		if (data->env[pos])
			remove_env(args[i], data);
		i++;
	}
	return (1);
}
