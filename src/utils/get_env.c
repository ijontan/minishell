/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:27:00 by itan              #+#    #+#             */
/*   Updated: 2023/08/07 18:25:33 by itan             ###   ########.fr       */
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

/**
 * @brief Get the env object
 *
 * @param envp env variables
 * @param name name of the env variable
 * @return char* pointer to the env variable
 */
char	*get_env(char **envp, char *name)
{
	int		len;
	char	*tmp;

	len = len_till_space(name);
	tmp = ft_calloc(sizeof(char), len + 2);
	ft_strlcpy(tmp, name, len + 1);
	tmp[len] = '=';
	while (*envp)
	{
		if (ft_strnstr(*envp, tmp, len + 1))
		{
			free(tmp);
			return (ft_strdup(*envp + len + 1));
		}
		envp++;
	}
	free(tmp);
	return (ft_strdup(""));
}
