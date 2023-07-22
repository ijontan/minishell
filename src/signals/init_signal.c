/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:33:45 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 23:13:41 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	init_signal(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.sigstatus = 0;
	g_sig.pid = 0;
}
