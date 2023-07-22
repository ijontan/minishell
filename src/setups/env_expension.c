/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/07/22 14:18:22 by nwai-kea         ###   ########.fr       */
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
	i = -1;
	while (arg[++i])
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
			i = -1;
			continue ;
		}
	}
	return (dst);
}

static char	**split_expand_recurse(char **args, char c, int count, int i)
{
	char	**cache;
	char	**dst;
	int		num;

	if (!*args)
		return (0);
	cache = ft_split(args[i], c);
	num = 0;
	while (cache[num])
		++num;
	if (args[i + 1])
		dst = split_expand_recurse(args, c, count + num, i + 1);
	else
		dst = (char **)ft_calloc(count + num + 1, sizeof(char *));
	ft_printf("count: %d, num: %d\n", count, num);
	while (num--)
		dst[count + num] = cache[num];
	free(cache);
	return (dst);
}

char	**split_expand(char **args, char sep)
{
	return (split_expand_recurse(args, sep, 0, 0));
}

void	expand_all_args(char **args, t_sh_data *data)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = env_expension(args[i], data->env);
		i++;
	}
}
