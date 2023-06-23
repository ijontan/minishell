/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:50:53 by itan              #+#    #+#             */
/*   Updated: 2023/06/23 13:11:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcmpn(char *str, char **seps)
{
	int	i;

	i = 0;
	while (seps && seps[i])
	{
		if (ft_strncmp(str, seps[i], ft_strlen(seps[i])) == 0)
			return (seps[i]);
		i++;
	}
	return (0);
}

static int	check_quoted(char *str, int i, int is_quoted)
{
	if ((str[i] == '"' || str[i] == '\'') && !is_quoted)
		is_quoted = str[i];
	else if (str[i] == is_quoted)
		is_quoted = 0;
	return (is_quoted);
}

static t_command_chunk	*recurse(char *str, char **seps, int depth)
{
	t_command_chunk	*dst;
	t_command_chunk	cache;
	int				is_quoted;
	int				i;

	is_quoted = 0;
	i = 0;
	cache.sep = 0;
	while (str[i] && (!ft_strcmpn(str + i, seps) || is_quoted))
		is_quoted = check_quoted(str, i++, is_quoted);
	cache.chunk = ft_substr(str, 0, i - !(!is_quoted));
	if (str[i] && ft_strcmpn(str + i, seps))
	{
		cache.sep = ft_strdup(ft_strcmpn(str + i, seps));
		i += ft_strlen(cache.sep);
	}
	if (!str[i])
		dst = (t_command_chunk *)ft_calloc(depth + 2, sizeof(t_command_chunk));
	else
		dst = recurse(str + i, seps, depth + 1);
	dst[depth] = cache;
	return (dst);
}

t_command_chunk	*split_command_chunks(char *str, char **seps)
{
	while (*str && ft_strcmpn(str, seps))
		str += ft_strlen(ft_strcmpn(str, seps));
	return (recurse(str, seps, 0));
}

// t_command_chunk	*split_commands(char *command)
// {
// 	t_command_chunk	*dst;
// 	char			**args;
// 	int				i;

// 	args = split_args(command, '|');
// 	return (dst);
// }
