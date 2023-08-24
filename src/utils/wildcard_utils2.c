/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:36:17 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/24 20:09:11 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrcmp(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;

	i = ft_abs(ft_strlen(str1) - ft_strlen(str2));
	j = 0;
	while (str1[i] == str2[j] && str1[i] && str2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[j]);
}

char	*ft_joinchar(char *path, char c)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dst = (char *)malloc(ft_strlen(path) + 2);
	if (!dst)
		return (0);
	while (path[j])
		dst[i++] = path[j++];
	dst[i++] = c;
	dst[i] = '\0';
	free(path);
	return (dst);
}

char	*ft_proc_sep(char *path)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup("");
	while (path[++i])
	{
		if (path[i] == ' ')
			tmp = ft_append(tmp, "\' \'");
		else if (path[i] == '\'')
			tmp = ft_append(tmp, "\"\'\"");
		else if (path[i] == '\"')
			tmp = ft_append(tmp, "\'\"\'");
		else
			tmp = ft_joinchar(tmp, path[i]);
	}
	return (tmp);
}
