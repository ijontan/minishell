/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:43:57 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 17:52:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_signal(int signo)
{
	(void)signo;
	g_sig.sigstatus = 130;
	exit(130);
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
	g_sig.sigstatus = 0;
}

void	clear_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
