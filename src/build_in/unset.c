/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:04:10 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/16 18:03:48 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char *args, t_sh_data *data, char **tmp)
{
	int	i;
	int	j;

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
}

static void	remove_env_no_equal(char *args, t_sh_data *data, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strcmp(args, data->env[i]) != 0)
			tmp[j++] = data->env[i];
		else
			free(data->env[i]);
		i++;
	}
}

int	unset(char **args, t_sh_data *data)
{
	int		i;
	int		pos;
	int		len;
	char	**tmp;

	if (!args[1])
	{
		ft_printf("unset: Too few arguments.\n");
		return (1);
	}
	i = 1;
	len = env_len(data->env);
	tmp = (char **)ft_calloc(len, sizeof(char *));
	while (args[i])
	{
		pos = find_env_pos(args[i], data->env);
		if (data->env[pos])
		{
			if (ft_hasequal(data->env[pos]))
				remove_env(args[i], data, tmp);
			else
				remove_env_no_equal(args[i], data, tmp);
		}
		i++;
	}
	free(data->env);
	data->env = tmp;
	return (1);
}
