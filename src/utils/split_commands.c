/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:50:53 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 18:19:27 by itan             ###   ########.fr       */
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

static int	count_word(char *str, char **seps, int *is_quoted,
		t_command_chunk *cache)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (ft_strcmpn(str + i, (char *[]){"&", "|", NULL}))
		cache->error = true;
	while (str[i] && (!ft_strcmpn(str + i, seps) || *is_quoted))
	{
		*is_quoted = check_quoted(str, i, *is_quoted);
		if (str[i] == '(' || str[i] == ')')
		{
			len = detect_brackets(str + i);
			if (len == -1 || len < 2)
				return (-1);
			i += len;
			cache->is_subshell = true;
		}
		i++;
	}
	return (i);
}

static t_command_chunk	*recurse(char *str, char **seps, int depth)
{
	t_command_chunk	*dst;
	t_command_chunk	cache;
	int				is_quoted;
	int				i;

	is_quoted = 0;
	cache.sep = 0;
	cache.is_subshell = false;
	cache.commands = NULL;
	cache.error = false;
	i = count_word(str, seps, &is_quoted, &cache);
	if (i == -1)
		return (NULL);
	cache.chunk = ft_substr(str, 0, i);
	if (str[i] && ft_strcmpn(str + i, seps))
	{
		cache.sep = ft_strdup(ft_strcmpn(str + i, seps));
		i += ft_strlen(cache.sep);
	}
	if (!str[i])
		dst = (t_command_chunk *)ft_calloc(depth + 3, sizeof(t_command_chunk));
	else
		dst = recurse(str + i, seps, depth + 1);
	dst[depth] = cache;
	return (dst);
}

t_command_chunk	*split_command_chunks(char *str, char **seps)
{
	t_command_chunk	*dst;
	int				i;

	while (*str == ' ' || *str == '\t')
		str++;
	while (*str && ft_strcmpn(str, seps))
	{
		str += ft_strlen(ft_strcmpn(str, seps));
		return (NULL);
	}
	dst = recurse(str, seps, 0);
	i = -1;
	while (dst[++i].chunk)
	{
		check_pipe_err(dst[i].chunk, &dst[i]);
		if (dst[i].error)
		{
			free_t_chunk_array(dst);
			return (NULL);
		}
	}
	return (dst);
}

// t_command_chunk	*split_commands(char *command)
// {
// 	t_command_chunk	*dst;
// 	char			**args;
// 	int				i;

// 	args = split_args(command, '|');
// 	return (dst);
// }
