/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:16:38 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 19:18:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_2d(char **args)
{
	char	**dup;
	int		i;

	i = 0;
	while (args[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (args[++i])
		dup[i] = ft_strdup(args[i]);
	return (dup);
}
