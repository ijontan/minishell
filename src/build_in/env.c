/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:38:47 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/14 00:49:23 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **args, char **env)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		while (env[i])
		{
			if ((long)ft_strchr(env[i], '=') != -1)
				ft_putendl_fd(env[i], 1);
			i++;
		}
	}
	else
	{
		ft_putendl_fd("minishell: env: Too many arguments.", 1);
		return (1);
	}
	return (0);
}
