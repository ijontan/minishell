/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:06:56 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 17:45:58 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_t_command(void *command)
{
	t_command	*tmp;

	tmp = (t_command *)command;
	free_2d(tmp->args);
	free(tmp);
}

void	free_t_chunk_array(t_command_chunk *command_chunks)
{
	int	i;

	i = -1;
	while (command_chunks[++i].chunk)
	{
		free(command_chunks[i].chunk);
		ft_lstclear(&command_chunks[i].commands, free_t_command);
	}
	free(command_chunks);
}
