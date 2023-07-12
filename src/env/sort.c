/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:54:03 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/06/23 17:18:20 by nwai-kea         ###   ########.fr       */
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

void	sorting_env(char **env, int len)
{
	int		i;
	int		status;
	char	*tmp;

	i = 0;
	status = 0;
	while (env && status == 0)
	{
		status = 1;
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
}

void	sort_env(char **env)
{
	int	i;
	int	len;

	i = 0;
	len = env_len(env);
	sorting_env(env, len);
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
