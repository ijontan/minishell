/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:15:13 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 18:18:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe_err(char *command, t_command_chunk *chunk)
{
	int	i;

	i = 0;
	while (command[i] == ' ')
		++i;
	if (command[i] == '|')
		chunk->error = SYNTAX_ERROR;
	i = ft_strlen(command) - 1;
	while (command[i] == ' ')
		--i;
	if (command[i] == '|')
		chunk->error = SYNTAX_ERROR;
}
