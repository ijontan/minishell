/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:43:57 by itan              #+#    #+#             */
/*   Updated: 2023/08/19 23:19:33 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_signal(int signo)
{
	(void)signo;
	g_sig.sigstatus = 130;
	write(1, "\n", 1);
}

void	quit_signal(int signo)
{
	(void)signo;
	g_sig.sigstatus = 131;
	ft_printf("Quit\n");
}

void	setup_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}

void	clear_signal(void)
{
	signal(SIGQUIT, quit_signal);
	signal(SIGINT, interrupt_signal);
}
