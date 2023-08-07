/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 11:38:43 by itan              #+#    #+#             */
/*   Updated: 2023/08/07 11:39:17 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_expand_recurse(char **args, int count, int i)
{
	char	**cache;
	char	**dst;
	int		num;

	if (!*args)
		return (0);
	cache = split_args(args[i]);
	num = 0;
	while (cache[num])
		++num;
	if (args[i + 1])
		dst = split_expand_recurse(args, count + num, i + 1);
	else
		dst = (char **)ft_calloc(count + num + 1, sizeof(char *));
	while (num--)
		dst[count + num] = cache[num];
	free(cache);
	return (dst);
}

void	split_expand(char ***args)
{
	char	**tmp2d;

	tmp2d = *args;
	*args = split_expand_recurse(*args, 0, 0);
	free_2d(tmp2d);
}
