/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:36:04 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 02:06:29 by itan             ###   ########.fr       */
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
		is_quoted = *command++;
	i = 0;
	while ((command[i] != ' ' || is_quoted) && command[i])
		if (command[i++] == is_quoted)
			break ;
	str = ft_substr(command, 0, i - !(!is_quoted));
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
char	**split_args(char *command)
{
	return (split_recurse(command, 0));
}
