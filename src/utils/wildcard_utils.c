/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:25:41 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/09 18:28:57 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_buffer(t_sh_data *data, struct dirent *filename, char *before,
		char *after)
{
	char	*buffer;

	buffer = NULL;
	if (!before && !after)
		buffer = find_all(data, filename);
	else if (!before && after)
		buffer = find_after(data, filename, after);
	else
		buffer = find_some(data, filename, before, after);
	return (buffer);
}

int	ft_ischar(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strndup(char *str, int n)
{
	char	*dst;
	int		i;

	dst = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (str[i] && i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strstr(char const *str, char const *substr)
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
			return (&((char *)str)[i]);
		i++;
	}
	return (0);
}

int	count_wc(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			count++;
		i++;
	}
	return (count);
}
