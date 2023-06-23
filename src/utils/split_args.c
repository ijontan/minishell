/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:36:04 by itan              #+#    #+#             */
/*   Updated: 2023/06/23 14:04:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_recurse(char *command, int depth)
{
	char	*str;
	char	**dst;
	int		i;
	int		is_quoted;

	is_quoted = 0;
	while (*command == ' ')
		command++;
	if (*command == '"' || *command == '\'')
		is_quoted = *command;
	i = 0;
	while ((command[i] != ' ' || is_quoted) && command[i])
		if (command[i++] == is_quoted)
			break ;
	str = ft_substr(command, 0, i);
	while (command[i] && command[i] == ' ')
		i++;
	if (!command[i])
		dst = (char **)ft_calloc(depth + 2, sizeof(char *));
	else
		dst = split_recurse(command + i, depth + 1);
	dst[depth] = str;
	return (dst);
}

// wrote this function to split the command into an array of arguments
// for example, "echo "hello world"" will be split into ["echo",
//	""hello world""]

/**
 * @brief split_args split the command into an array of arguments.
 * for example, "echo "hello world"" will be split into ["echo",
 * "hello world"]
 *
 * @param command
 * @return char**
 */
char	**split_args(char *command)
{
	if (!command)
		return (0);
	while (*command && *command == ' ')
		command++;
	if (!*command)
		return (ft_calloc(1, sizeof(char *)));
	return (split_recurse(command, 0));
}
