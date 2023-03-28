/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:36:04 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 01:28:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_recurse(char *command, int depth)
{
	char	*str;
	char	**dst;
	int		i;
	bool	is_quoted;

	i = -1;
	is_quoted = false;
	while ((command[++i] != ' ' || is_quoted) && command[i])
		if (command[i] == '\"')
			is_quoted = !is_quoted;
	str = ft_substr(command, 0, i);
	if (!command[i])
	{
		dst = (char **)ft_calloc(depth + 2, sizeof(char *));
		dst[depth] = str;
		return (dst);
	}
	dst = split_recurse(command + i + 1, depth + 1);
	dst[depth] = str;
	return (dst);
}

// wrote this function to split the command into an array of arguments
// for example, "echo "hello world"" will be split into ["echo",
//	""hello world""]
char	**split_args(char *command)
{
	return (split_recurse(command, 0));
}
