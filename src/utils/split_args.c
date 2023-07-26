/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:22:47 by itan              #+#    #+#             */
/*   Updated: 2023/07/26 21:00:53 by itan             ###   ########.fr       */
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

static char	*move_to_next(char *str, int *i, char **seps, int *dept)
{
	char	*sep;

	sep = NULL;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] && ft_strcmpn(str + *i, seps))
	{
		sep = ft_strdup(ft_strcmpn(str + *i, seps));
		(*i) += ft_strlen(sep);
		(*dept)++;
	}
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
	{
		free(sep);
		return (ft_strdup("SOme RanDom Error COde that wiLL never be used"));
	}
	return (sep);
}

static char	**recurse(char *str, char **seps, int dept)
{
	char	**dst;
	char	*cache;
	char	*sep;
	int		is_quoted;
	int		i;

	is_quoted = 0;
	sep = NULL;
	i = 0;
	while (str[i] && (!ft_strcmpn(str + i, seps) || is_quoted))
		is_quoted = check_quoted(str, i++, is_quoted);
	cache = ft_substr(str, 0, i);
	sep = move_to_next(str, &i, seps, &dept);
	if (!str[i])
		dst = (char **)ft_calloc(dept + 2, sizeof(char *));
	else
		dst = recurse(str + i, seps, dept + 1);
	if (sep)
		dst[dept--] = sep;
	dst[dept] = cache;
	return (dst);
}

char	**split_args(char *command)
{
	int		dept;
	int		i;
	char	**seps;
	char	*sep;
	char	**dst;

	i = 0;
	dept = 0;
	seps = (char *[]){"<<", ">>", "<", ">", " ", NULL};
	sep = move_to_next(command, &i, seps, &dept);
	dst = recurse(command + i, seps, dept);
	if (sep)
		dst[0] = sep;
	return (dst);
}
