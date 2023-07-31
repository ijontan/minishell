/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:25:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/31 23:28:22 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr2(char const *str, char const *substr)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	if (!*substr)
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while ((char)str[i + j] == (char)substr[j] && (char)str[i + j])
			j++;
		if (!substr[j])
			return (&((char *)str)[i + j + 1]);
		i++;
	}
	return (0);
}

int	compare_str(char *arg, char **chr, char *dname)
{
	int	i;
	char	*tmp;

	i = 0;
	if (arg[0] != '*' && (ft_strncmp(dname, chr[0], ft_strlen(chr[0])) != 0))
		return (-1);
	if (arg[0] == '*')
	{
		if (ft_strchr(dname, chr[i][0]))
			tmp = ft_strchr(dname, chr[i][0]);
		else
			return (-1);
	}
	tmp = dname;
	while (chr[i])
	{
		if (!chr[i + 1])
			break ;
		tmp = ft_strstr2(tmp, chr[i]);
		if ((!tmp && chr[i + 1]))
			return (-1);
		else
			i++;
	}
	if ((arg[ft_strlen(arg) - 1] != '*' && (ft_strcmp(tmp, chr[i]) != 0)) ||
		(arg[ft_strlen(arg) - 1] == '*'  && (ft_strncmp(tmp, chr[i], ft_strlen(chr[i])) != 0)))
		return (-1);
	else
		return (1);
}

char    *multiple_wildcards(char *arg, t_sh_data *data, struct dirent *filename)
{
    char	**c;
	char	*tmp;

	c = ft_split(arg, '*');
	// int	i = 0;
	// while (c[i])
	// 	printf("%s\n", c[i++]);
	tmp = ft_strdup("");
	while (filename)
	{
		if (compare_str(arg, c, filename->d_name) > 0)
		{
			if (tmp[0])
				tmp = ft_strjoin(tmp, " ");
			tmp = ft_strjoin(tmp, filename->d_name);
		}
		filename = readdir(data->dir);
	}
	return (tmp);
}