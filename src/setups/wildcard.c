/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:21:46 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/19 01:12:35 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_all(char *arg, t_sh_data *data, struct dirent *filename)
{
	char	*tmp;
	int		check;

	tmp = ft_strdup("");
	check = 0;
	while (filename)
	{
		if (filename->d_name[0] != '.')
		{
			tmp = ft_strjoin(tmp, filename->d_name);
			check = 1;
		}
		filename = readdir(data->dir);
		if (filename && check)
			tmp = ft_strjoin(tmp, " ");
	}
	if (tmp[0])
		free(arg);
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
			if (!after || (after && ft_strnstr(filename->d_name, after, 255)))
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

void	find_after(char *arg, t_sh_data *data, struct dirent *filename,
		char *after)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (filename)
	{
		if (ft_strnstr(filename->d_name, after, 255))
		{
			if (tmp[0])
				tmp = ft_strjoin(tmp, " ");
			tmp = ft_strjoin(tmp, filename->d_name);
		}
		filename = readdir(data->dir);
	}
	if (tmp[0])
		free(arg);
}

void	expand_wildcard(char *arg, t_sh_data *data, struct dirent *filename)
{
	char	*before;
	char	*after;
	char	*buffer;
	int		i;

	before = NULL;
	after = NULL;
	i = 0;
	while (arg[i] != '*' && arg[i])
		i++;
	if (i > 0)
		before = ft_substr(arg, 0, i);
	if (arg[i + 1])
		after = ft_strdup(arg);
	if (!before && !after)
		find_all(arg, data, filename);
	else if (!before && after)
		find_after(arg, data, filename, after);
	else
		buffer = find_some(data, filename, before, after);
	(void)buffer; // ! remove when need to use
}

void	wildcard(char *arg, t_sh_data *data)
{
	struct dirent	*filename;

	(void)arg;
	data->dir = opendir(".");
	if (!data->dir)
	{
		perror("opendir");
		exit(-1);
	}
	filename = readdir(data->dir);
	expand_wildcard(arg, data, filename);
	closedir(data->dir);
}
