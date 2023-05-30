/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:46:06 by itan              #+#    #+#             */
/*   Updated: 2023/05/30 23:27:32 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO: implement update to the env variable

/**
 * @brief cd should change the current working directory
 * 
 * @param args place holder parameter for now
 */

static void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

static int	update_oldpwd(void)
{
	char	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (!cwd)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
}

static int	to_path(int path)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (path == 0)
	{
		env_path = get_path("HOME", 4);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : HOME not set", STDERR);
		if (env_path == NULL)
			return (1);
	}
	else if (path == 1)
	{
		env_path = get_path("OLDPWD", 6);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : OLDPWD not set", STDERR);
		if (env_path == NULL)
			return (1);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

static int	check_args(char **args)
{
	char	*cwd;
	char	buffer[4097];

	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("minishell : cd : too many arguments\n", STDERR);
			return (1);
		}
		cwd = getcwd(buffer, 4096);
	}
}

void	cd(char **args)
{
	if (args[1] == NULL || args[1], "~")
		return (to_path(0));
	if (chdir(args[1]) != 0)
	{
		perror("minishell");
	}
	else
	{
		if (args[1][0] == '-' && !args[1][2])
		{
			return (to_path(1));
		}
	}
}
