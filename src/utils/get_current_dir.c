/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:01:27 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 19:06:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_dir(void)
{
	char	*cwd;
	char	*tmp;
	int		len;
	int		i;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell");
		return (NULL);
	}
	len = ft_strlen(cwd);
	i = len;
	while (i >= 0 && cwd[i] != '/')
		i--;
	tmp = ft_substr(cwd, i + 1, len - i);
	free(cwd);
	return (tmp);
}
