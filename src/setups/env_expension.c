/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/08/07 12:27:00 by itan             ###   ########.fr       */
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

char	*env_expension_len(char *arg, int len, char **env)
{
	char	*dst;
	char	*tmp;
	int		i;

	dst = NULL;
	i = -1;
	while (arg[++i] && i < len)
	{
		while (arg[i] && arg[i] != '$' && i < len)
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

static int	len_till_quote(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i++;
	while (str[i] && str[i] != '"' && str[i] != '\'')
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
	int		i;
	int		len;
	char	*tmp;
	char	*dst;

	i = 0;
	dst = NULL;
	while (arg[i])
	{
		len = len_till_quote(arg + i) - 1;
		if (arg[i] == '\'')
			tmp = ft_substr(arg + i, 0, len);
		else
			tmp = env_expension_len(arg + i, len, env);
		ft_printf("src: %s\n", arg + i);
		ft_printf("len: %d\n", len);
		ft_printf("tmp: %s\n", tmp);
		ft_printf("dst: %s\n\n", dst);
		i += len + 1;
		dst = ft_append(dst, tmp);
		free(tmp);
		if (!arg[i] || len == 0)
			break ;
	}
	return (dst);
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
		args[i] = env_expension(args[i], data->env);
		free(tmp);
	}
	split_expand(&(cmd->args));
	args = cmd->args;
	i = -1;
	while (args[++i])
	{
		tmp = args[i];
		args[i] = remove_quote(args[i], cmd);
		free(tmp);
	}
}
