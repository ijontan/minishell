/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:51:33 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 20:59:06 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!args[i])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
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
