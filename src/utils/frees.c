/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:06:56 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 17:20:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_t_command(void *command)
{
	t_command	*tmp;

	tmp = (t_command *)command;
	if (tmp->args)
		free_2d(tmp->args);
	free(tmp);
}

void	free_t_chunk_array(t_command_chunk *command_chunks)
{
	int	i;

	i = -1;
	if (!command_chunks)
		return ;
	while (command_chunks[++i].chunk)
	{
		free(command_chunks[i].chunk);
		if (command_chunks[i].commands)
			ft_lstclear(&command_chunks[i].commands, free_t_command);
		if (command_chunks[i].sep)
			free(command_chunks[i].sep);
	}
	free(command_chunks);
}
