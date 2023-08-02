/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:36:17 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/08/02 22:01:20 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strrcmp(const char *str1, const char *str2, size_t n)
{
    size_t  i;
    size_t  j;

    if (!n)
		return (-1);
	i = ft_strlen(str1) - ft_strlen(str2);
    j = 0;
	while (str1[i] == str2[j] && str1[i] && str2[j])
	{
		i++;
        j++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[j]);
}