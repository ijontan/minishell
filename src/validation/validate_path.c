/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 00:05:57 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 19:22:34 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return (*envp);
		envp++;
	}
	perror("PATH not found");
	exit(127);
	return (NULL);
}

char	*check_path_exist(char *program_name, char **envp)
{
	char	**paths;
	char	*dst;
	int		i;

	i = 0;
	dst = NULL;
	program_name = ft_strjoin("/", program_name);
	paths = ft_split(get_path(envp) + 5, ':');
	while (paths[i])
	{
		dst = ft_strjoin(paths[i++], program_name);
		if (!access(dst, F_OK))
		{
			free(program_name);
			free_2d(paths);
			return (dst);
		}
		if (dst)
			free(dst);
	}
	free(program_name);
	free_2d(paths);
	perror("program doesn't exist in path");
	return (NULL);
}

char	*check_program_exist(char *program_name, char **env)
{
	if (program_name[0] == '/' || program_name[0] == '.')
	{
		if (!access(program_name, F_OK))
			return (program_name);
		perror("program doesn't exist");
		return (NULL);
	}
	else
		return (check_path_exist(program_name, env));
}
