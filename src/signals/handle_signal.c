/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:02:38 by itan              #+#    #+#             */
/*   Updated: 2023/04/03 14:15:34 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief handle the signal
 * 
 * @param signo 
 */
void	handle_signal(int signo)
{
	if (signo == SIGINT)
		ft_printf("\b\b  \n%s", rl_prompt);
}
