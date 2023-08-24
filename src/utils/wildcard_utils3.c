/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:08:27 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/24 20:45:13 by nwai-kea         ###   ########.fr       */
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
	while (*command == '*')
		command++;
	i = 0;
	while (command[i] && (command[i] != '*' || is_quoted))
		is_quoted = check_quoted(command, i++, is_quoted);
	str = ft_substr(command, 0, i);
	while (command[i] && command[i] == '*')
		i++;
	if (!command[i])
		dst = (char **)ft_calloc(depth + 2, sizeof(char *));
	else
		dst = split_recurse(command + i, depth + 1);
	dst[depth] = str;
	return (dst);
}

static char	**split_commands(char *command)
{
	return (split_recurse(command, 0));
}

char	*ft_proc_sep_2(char *path)
{
	int		i;
	char	*tmp;
	char	quote;

	i = -1;
	quote = 0;
	tmp = ft_strdup("");
	while (path[++i])
	{
		if ((path[i] == '\'' || path[i] == '"') && !quote)
			quote = path[i];
		else if (path[i] == quote)
			quote = 0;
		if (path[i] == '*' && quote == '"')
			tmp = ft_append(tmp, "\'*\'");
		else if (path[i] == '*' && quote == '\'')
			tmp = ft_append(tmp, "\"*\"");
		else
			tmp = ft_joinchar(tmp, path[i]);
	}
	return (tmp);
}

char	**wildcard_split(char *src)
{
	char	**dst;
	int		i;

	i = -1;
	dst = split_commands(src);
	while (dst && dst[++i])
		replace_free(dst + i, remove_quote(dst[i], NULL));
	return (dst);
}
