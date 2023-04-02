/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:42:38 by itan              #+#    #+#             */
/*   Updated: 2023/04/02 21:53:33 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: add env expansion to this function
//TODO: add redirection to this function
//TODO: add heredoc to this function

/**
 * @brief Split the input string into command blocks
 * 
 * @param args The string to split
 * @return t_command* The array of command blocks
 */
t_command	*tokenize(char *command)
{
	t_command	*dst;
	char		**args;
	int			i;

	args = ft_split(command, '|');
	i = 0;
	while (args[i])
		i++;
	dst = (t_command *)ft_calloc(i + 1, sizeof(t_command));
	i = 0;
	while (args[i])
	{
		dst[i].args = split_args(args[i]);
		i++;
	}
	return (dst);
}
