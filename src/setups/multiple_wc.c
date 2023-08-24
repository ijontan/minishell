/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:25:57 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/24 20:06:41 by nwai-kea         ###   ########.fr       */
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
			return (&((char *)str)[i + 1]);
		i++;
	}
	return (0);
}

char	*ft_strrstr(char const *str, char const *substr)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	if (!*substr)
		return (0);
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		j = 0;
		if ((char)str[i - j] == (char)substr[j] && (char)str[i - j])
		{
			if (ft_strncmp(&((char *)str)[i], substr, ft_strlen(substr)) == 0)
				return (&((char *)str)[i]);
		}
		i--;
	}
	return (0);
}

char	*first_wc(char **chr, char *dname)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strchr(dname, chr[i][0]))
		tmp = ft_strchr(dname, chr[i][0]);
	else
		return (0);
	return (tmp);
}

int	compare_str(char *arg, char **chr, char *dname)
{
	int		i;
	char	*tmp;

	i = 0;
	if (arg[0] != '*' && (ft_strncmp(dname, chr[0], ft_strlen(chr[0])) != 0))
		return (-1);
	if (arg[0] == '*')
		tmp = first_wc(chr, dname);
	tmp = dname;
	while (chr[i])
	{
		if (!chr[i + 1])
			break ;
		tmp = ft_strstr2(tmp, chr[i]);
		if ((!tmp && chr[i + 1]))
			return (-1);
		else if (!chr[i + 1])
			break ;
		i++;
	}
	if ((arg[ft_strlen(arg) - 1] != '*' && (ft_strrcmp(tmp, chr[i]) != 0))
		|| ((arg[ft_strlen(arg) - 1] == '*' && (ft_strrstr(tmp, chr[i]) == 0))))
		return (-1);
	return (1);
}

char	*multiple_wildcards(char *arg, t_sh_data *data, struct dirent *filename)
{
	char	**c;
	char	*tmp;
	char	*new;

	if (count_wc(arg) <= 1 && *arg == '*' && ft_strlen(arg) == 1)
		return (expand_wildcard(arg, data, filename));
	c = wildcard_split(arg);
	tmp = ft_strdup("");
	while (filename)
	{
		if (compare_str(arg, c, filename->d_name) > 0)
		{
			if (tmp[0])
				tmp = ft_append(tmp, " ");
			new = ft_proc_sep(filename->d_name);
			tmp = ft_append(tmp, new);
			free(new);
		}
		filename = readdir(data->dir);
	}
	free_2d(c);
	return (tmp);
}
