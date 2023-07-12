/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:15:34 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 20:15:48 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strstart(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_env_pos(char *args, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(args, "=");
		if (ft_strstart(tmp, env[i]))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (i);
}

int	env_valid(char *env)
{
	int	i;

	i = 0;
	if (env[i] == '=')
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalpha(env[i]))
			return (0);
		i++;
	}
	return (1);
}
