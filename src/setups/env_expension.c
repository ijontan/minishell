/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/06/23 17:17:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_till_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	return (i);
}

/**
 * @brief Expends the env variables in the argument
 *
 * @param arg argument to be expended
 * @param env env variables
 * @return char* expended argument
 */
char	*env_expension(char *arg, char **env)
{
	char	*dst;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		len;

	dst = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			tmp = ft_substr(arg, 0, i);
			tmp2 = ft_append(dst, tmp);
			free(tmp);
			len = len_till_space(arg + i + 1);
			tmp = get_env(env, arg + i + 1);
			dst = ft_append(tmp2, tmp);
			free(tmp);
			arg += i + len + 1;
			i = 0;
			continue ;
		}
		i++;
	}
	return (dst);
}
