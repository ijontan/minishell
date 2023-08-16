/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:51:33 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/12 19:17:57 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char *args)
{
	int	i;

	i = 0;
	if (!args || !args[i])
		return (1);
	if (args[i] == '-')
		i++;
	while (args[i] && args[i] == 'n')
		i++;
	if (!args[i])
		return (0);
	return (1);
}

int	echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!args[i])
	{
		write(1, "\n", 1);
		return (1);
	}
	while (args[i] && !check_n(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
