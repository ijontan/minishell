/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:13:15 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/12 18:03:05 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_chunk	*init_brackets(t_command_chunk *chunk)
{
	chunk = (t_command_chunk *)malloc(sizeof(t_command_chunk));
	chunk->count = 0;
	chunk->subshell = false;
	return (chunk);
}

int	detect_brackets(t_command_chunk *chunk, char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '(')
		{
			if (chunk->count == 0)
				chunk->commands->content = cmd;
			chunk->count++;
		}
		else if (*cmd == ')')
			chunk->count--;
		if (chunk->count > 0)
			chunk->subshell = true;
		cmd++;
	}
	if (chunk->count != 0 && !cmd)
		return (1);
	return (0);
}

// void	parentheses(t_command_chunk *chunk, char *cmd)
// {
// 	if (detect_brackets(chunk, cmd))

// }