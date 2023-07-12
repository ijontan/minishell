/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:02:38 by itan              #+#    #+#             */
/*   Updated: 2023/06/30 17:20:19 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief handle interruption signals
 * 
 * @param signo 
 */
void	handle_signal(int signo)
{
	(void)signo;
	g_sig.sigint = 1;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.sigstatus = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.sigstatus = 130;
	}
}

void	handle_signal_quit(int signo)
{
	char	*nbr;

	(void)signo;
	nbr = ft_itoa(signo);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_sig.sigstatus = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}
