/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:54:03 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/14 00:58:39 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**sorting_env(char **env, int len)
{
	int		i;
	int		status;
	char	*tmp;

	status = 0;
	while (env && status == 0)
	{
		status = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				status = 0;
			}
			i++;
		}
		len--;
	}
	return (env);
}

void	sort_env(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = env_len(env);
	env = sorting_env(env, len);
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
