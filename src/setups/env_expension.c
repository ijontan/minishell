/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/08/22 04:59:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollar_return(char *arg, char *prev, int i, t_sh_data *data)
{
	char	*tmp;

	free(prev);
	if (arg[i + 1] == '?')
		tmp = ft_itoa(data->status);
	else if (arg[i + 1] == '$')
		tmp = ft_itoa(g_sig.pid);
	else if (!arg[i + 1] || arg[i + 1] == ' ' || !ft_strcmp(arg, "\"$\""))
		tmp = ft_strdup("$");
	else
		tmp = get_env(data->env, arg + i + 1);
	return (tmp);
}

char	*env_expension_len(char *arg, t_sh_data *data)
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
			tmp = dollar_return(arg, tmp, i, data);
			if (arg[i + 1] == '?' || arg[i + 1] == '$' || !arg[i + 1])
				i++;
			arg += len_till_space(arg + i + 1) + 1;
		}
		dst = ft_append(dst, tmp);
		free(tmp);
		arg += i;
		i = -1;
	}
	return (dst);
}

static char	*substr_append(char *dst, char **src, int *i, t_sh_data *data)
{
	char	*tmp;
	char	*tmp2;

	if ((**src == '\'' || **src == '"') && (*i) != 0)
		(*i)++;
	tmp = ft_substr(*src, 0, *i);
	if ((*src)[*i - **src == '\'' || **src == '"'] != '\'' || **src != '\'')
	{
		tmp2 = env_expension_len(tmp, data);
		free(tmp);
		tmp = tmp2;
	}
	dst = ft_append(dst, tmp);
	free(tmp);
	(*src) += *i;
	(*i) = -1;
	return (dst);
}

char	*env_expension(char *str, t_sh_data *data)
{
	int		i;
	char	*dst;
	char	quote;

	i = -1;
	dst = NULL;
	quote = 0;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
		{
			quote = str[i];
			if (i != 0)
				dst = substr_append(dst, &str, &i, data);
		}
		else if (str[i] == quote)
		{
			quote = 0;
			dst = substr_append(dst, &str, &i, data);
		}
	}
	dst = substr_append(dst, &str, &i, data);
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
		args[i] = env_expension(args[i], data);
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
