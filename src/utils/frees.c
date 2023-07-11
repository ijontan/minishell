/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:06:56 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 14:19:52 by itan             ###   ########.fr       */
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

static void	free_t_chunk(void *chunk)
{
	t_command_chunk	*tmp;

	tmp = (t_command_chunk *)chunk;
	free(tmp->chunk);
	ft_lstclear(&tmp->commands, free_t_command);
	free(tmp);
}

void	free_t_chunk_list(t_list **list)
{
	ft_lstclear(list, free_t_chunk);
}

void	free_sh_data(t_sh_data *data)
{
	free_2d(data->env);
	free(data->prompt);
	free_t_chunk_list(&data->command_chunks);
}
