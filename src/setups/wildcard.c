/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:21:46 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/03 23:36:04 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_all(t_sh_data *data, struct dirent *filename)
{
	char	*tmp;
	int		check;

	tmp = ft_strdup("");
	check = 0;
	while (filename)
	{
		if (filename->d_name[0] != '.')
		{
			tmp = ft_append(tmp, filename->d_name);
			check = 1;
		}
		filename = readdir(data->dir);
		if (filename && check)
			tmp = ft_append(tmp, " ");
	}
	return (tmp);
}

char	*find_some(t_sh_data *data, struct dirent *filename, char *before,
		char *after)
{
	char	*tmp;
	int		len;

	tmp = ft_strdup("");
	while (filename)
	{
		len = ft_strlen(before);
		if (!ft_strncmp(filename->d_name, before, len))
		{
			if (!after || (after && ft_strstr(filename->d_name, after)))
			{
				if (tmp[0])
					tmp = ft_strjoin(tmp, " ");
				tmp = ft_strjoin(tmp, filename->d_name);
			}
		}
		filename = readdir(data->dir);
	}
	return (tmp);
}

char	*find_after(t_sh_data *data, struct dirent *filename, char *after)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (filename)
	{
		if (ft_strstr(filename->d_name, after))
		{
			if (tmp[0])
				tmp = ft_append(tmp, " ");
			tmp = ft_append(tmp, filename->d_name);
		}
		filename = readdir(data->dir);
	}
	return (tmp);
}

char	*expand_wildcard(char *arg, t_sh_data *data, struct dirent *filename)
{
	char	*before;
	char	*after;
	char	*buffer;
	int		i;

	before = NULL;
	after = NULL;
	buffer = NULL;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
		{
			if (i > 0)
				before = ft_substr(arg, 0, i);
			if (arg[i + 1])
				after = ft_strdup(arg + (i + 1));
			buffer = write_buffer(data, filename, before, after);
			free(before);
			free(after);
		}
		i++;
	}
	return (buffer);
}

char	*wildcard(char *arg, t_sh_data *data)
{
	struct dirent	*filename;
	char			*result;

	result = NULL;
	data->dir = opendir(".");
	if (!data->dir)
	{
		perror("opendir");
		exit(-1);
	}
	filename = readdir(data->dir);
	if (ft_ischar(arg, '*'))
		arg = "*";
	if (count_wc(arg) <= 1)
		result = expand_wildcard(arg, data, filename);
	else
		result = multiple_wildcards(arg, data, filename);
	closedir(data->dir);
	return (result);
}