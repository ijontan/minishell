/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/07/25 17:57:03 by itan             ###   ########.fr       */
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
	while (num--)
		dst[count + num] = cache[num];
	free(cache);
	return (dst);
}

char	**split_expand(char **args, char sep)
{
	return (split_expand_recurse(args, sep, 0, 0));
}

void	expand_all_args(t_command *cmd, t_sh_data *data)
{
	int		i;
	char	*tmp;
	char	**args;
	char	first_char;

	args = cmd->args;
	i = -1;
	while (args[++i])
	{
		first_char = args[i][0];
		if (first_char == '\'' || first_char == '"')
		{
			tmp = args[i];
			args[i] = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
			free(tmp);
		}
		if (first_char == '\'')
			continue ;
		tmp = args[i];
		args[i] = env_expension(args[i], data->env);
		free(tmp);
	}
	cmd->args = split_expand(args, ' ');
	free_2d(args);
}
