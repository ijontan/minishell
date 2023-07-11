/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:13:15 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/11 00:41:48 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_brackets(t_command_chunk *chunk, char *cmd)
{
	int	i;

	i = 0;
	chunk->count = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '(')
			chunk->count++;
		if (cmd[i] == ')')
			chunk->count--;
		if (chunk->count > 0)
			chunk->subshell = true;
		i++;
	}
	if (chunk->count != 0 && !cmd)
		return (1);
	return (0);
}

// void	parentheses(t_command_chunk *chunk, char *cmd)
// {
// 	if (detect_brackets(chunk, cmd))

// }