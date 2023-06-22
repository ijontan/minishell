/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:50:53 by itan              #+#    #+#             */
/*   Updated: 2023/06/21 20:33:58 by itan             ###   ########.fr       */
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

static char	**recurse(char *str, char **seps, int dept)
{
	char	**dst;
	char	*cache;
	int		is_quoted;
	int		i;

	is_quoted = 0;
	while (*str && ft_strcmpn(str, seps))
		str += ft_strlen(ft_strcmpn(str, seps));
	i = 0;
	while (str[i] && (!ft_strcmpn(str + i, seps) || is_quoted))
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quoted)
			is_quoted = str[i++];
		else if (str[i++] == is_quoted)
			is_quoted = 0;
	}
	cache = ft_substr(str, 0, i - !(!is_quoted));
	while (str[i] && ft_strcmpn(str + i, seps))
		i += ft_strlen(ft_strcmpn(str + i, seps));
	if (!str[i])
		dst = (char **)ft_calloc(dept + 2, sizeof(char *));
	else
		dst = recurse(str + i, seps, dept + 1);
	dst[dept] = cache;
	return (dst);
}

char	**split_strseps(char *str, char **seps)
{
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
