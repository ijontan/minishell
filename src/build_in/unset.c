/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:04:10 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 20:27:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env(char **env, int pos)
{
	int	i;
	int	count;

	free(env[pos]);
	env[pos] = NULL;
	i = pos;
	count = pos + 1;
	while (env[i + 1])
	{
		env[i] = ft_strdup(env[i + 1]);
		free(env[i + 1]);
		i++;
		count++;
	}
}

int	unset(char **args, char **env)
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
		pos = find_env_pos(args[i], env);
		if (env[pos])
			remove_env(env, pos);
	}
	return (1);
}
