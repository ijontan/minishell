/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/07/26 21:32:58 by itan             ###   ########.fr       */
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
	int		i;

	dst = NULL;
	i = -1;
	while (arg[++i])
	{
		while (arg[i] && arg[i] != '$')
			i++;
		tmp = ft_substr(arg, 0, i);
		if (arg[i] == '$')
		{
			dst = ft_append(dst, tmp);
			free(tmp);
			tmp = get_env(env, arg + i + 1);
			arg += len_till_space(arg + i + 1) + 1;
		}
		dst = ft_append(dst, tmp);
		free(tmp);
		arg += i;
		i = -1;
	}
	return (dst);
}

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

void	expand_all_args(t_command *cmd, t_sh_data *data)
{
	int		i;
	char	*tmp;
	char	**args;

	args = cmd->args;
	i = -1;
	while (args[++i])
	{
		tmp = args[i];
		args[i] = remove_quote(args[i], cmd, data);
		free(tmp);
	}
	split_expand(&(cmd->args));
}
