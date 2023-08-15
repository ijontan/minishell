/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:57:47 by itan              #+#    #+#             */
/*   Updated: 2023/08/16 00:23:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*substr_append(char *dst, char **src, int *i)
{
	char	*tmp;

	if (**src == '\'' || **src == '"')
		tmp = ft_substr(*src + 1, 0, *i - 1);
	else
		tmp = ft_substr(*src, 0, *i);
	dst = ft_append(dst, tmp);
	free(tmp);
	(*src) += *i + 1;
	(*i) = -1;
	return (dst);
}

char	*remove_quote(char *str, t_command *cmd)
{
	int		i;
	char	*dst;
	char	quote;

	quote = 0;
	i = -1;
	dst = NULL;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
		{
			quote = 0;
			dst = substr_append(dst, &str, &i);
		}
	}
	dst = ft_append(dst, str);
	if (quote)
		cmd->error = 1;
	return (dst);
}
