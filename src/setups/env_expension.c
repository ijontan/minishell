/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:24 by itan              #+#    #+#             */
/*   Updated: 2023/08/13 21:49:52 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_till_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '$')
		i++;
	return (i);
}

static char	*dollar_return(char *arg, int i, t_sh_data *data)
{
	char	*tmp;

	if (arg[i + 1] == '?')
		tmp = ft_itoa(data->status);
	else if (arg[i + 1] == '$')
		tmp = ft_itoa(g_sig.pid);
	else if (!arg[i + 1])
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
			free(tmp);
			tmp = dollar_return(arg, i, data);
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

	tmp = ft_substr(*src, 0, *i);
	if ((*src)[*i] != '\'' || **src != '\'')
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
	quote = -1;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i] == quote)
		{
			i++;
			quote = -1;
			dst = substr_append(dst, &str, &i, data);
		}
		else if ((str[i] == '"' || str[i] == '\'') && str[0])
			quote = str[i];
		else if ((str[i] == '"' || str[i] == '\''))
		{
			quote = str[i];
			dst = substr_append(dst, &str, &i, data);
			i++;
		}
	}
	dst = substr_append(dst, &str, &i, data);
	return (dst);
}

// static int	len_till_quote(char *str, char quote)
// {
// 	int	i;

// 	i = 0;
// 	if (quote == 0)
// 	{
// 		while (str[i] && str[i] != '"' && str[i] != '\'')
// 			i++;
// 		return (i);
// 	}
// 	if (str[i] == quote)
// 		i++;
// 	while (str[i] && str[i] != quote)
// 		i++;
// 	return (i);
// }

/**
 * @brief Expends the env variables in the argument
 *
 * @param arg argument to be expended
 * @param env env variables
 * @return char* expended argument
 */
// char	*env_expension(char *arg, char **env)
// {
// 	int		i;
// 	int		len;
// 	char	*tmp;
// 	char	*dst;
// 	char	quote;

// 	i = 0;
// 	dst = NULL;
// 	quote = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '\'' || arg[i] == '"')
// 			quote = arg[i];
// 		len = len_till_quote(arg + i, quote);
// 		tmp = ft_substr(arg + i, 0, len);
// 		if (quote == '"')
// 		{
// 			tmp = env_expension_len(tmp, env);
// 		}
// 		ft_printf("src: %s\n", arg + i);
// 		ft_printf("len: %d\n", len);
// 		ft_printf("tmp: %s\n", tmp);
// 		ft_printf("dst: %s\n\n", dst);
// 		i += len + 1;
// 		dst = ft_append(dst, tmp);
// 		free(tmp);
// 		if (len == 0)
// 			break ;
// 	}
// 	return (dst);
// }

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
