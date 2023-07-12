/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:38:47 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 19:14:05 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **args, char **env)
{
	int	i;

	i = 0;
	if (!args[0])
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '=') != 0)
				ft_putstr_fd(env[i], 1);
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
