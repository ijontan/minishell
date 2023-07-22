/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:25:41 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/19 23:25:58 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
