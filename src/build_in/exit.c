/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:32:27 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/06/26 00:03:51 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit(t_sh_data *data, int argc, char **args)
{
	int	i;

	ft_putstr_fd("exit", 2);
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	while (args[0])
	{
		if (!ft_isnum(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		i++;
	}
	if (args[1])
		data->exited = ft_atoi(args[1]);
	else
		data->exited = 0;
}
