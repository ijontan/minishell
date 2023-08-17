/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 03:51:58 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/18 04:23:43 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_sh_data *data)
{
	int level_digit;
	char *lvl;
	char *arg;
	char *new_lvl;

	lvl = get_env(data->env, "SHLVL");
	level_digit = ft_atoi(lvl) + 1;
	new_lvl = ft_itoa(level_digit);
	arg = ft_strjoin("SHLVL=", new_lvl);
	overwrite_var(arg, data);
	free(lvl);
	free(new_lvl);
	free(arg);
}