/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:46:06 by itan              #+#    #+#             */
/*   Updated: 2023/06/20 23:42:43 by nwai-kea         ###   ########.fr       */
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

static int	update_oldpwd(char **env)
{
	char	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (!cwd)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!check_program_exist(oldpwd, env))
		add_env(oldpwd, env);
	ft_memdel(oldpwd);
	return (1);
}

static int	to_path(int path, t_sh_data *data)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (path == 0)
	{
		update_oldpwd(data->env);
		env_path = check_program_exist("HOME", data->env);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : HOME not set", STDERR);
		if (env_path == NULL)
			return (1);
	}
	else if (path == 1)
	{
		env_path = check_program_exist("OLDPWD", data->env);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : OLDPWD not set", STDERR);
		if (env_path == NULL)
			return (1);
		update_oldpwd(data->env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

static int	check_args(char **args)
{
	char	*cwd;
	char	buffer[4097];

	if (args[0])
	{
		if (args[1])
		{
			ft_putendl_fd("minishell : cd : too many arguments\n", STDERR);
			return (1);
		}
		cwd = getcwd(buffer, 4096);
	}
	return (0);
}

void	cd(char **args, t_sh_data *data)
{
	if (args[0] == NULL || args[0] == "~")
		return (to_path(0));
	if (chdir(args[0]) != 0)
	{
		perror("minishell");
	}
	else
	{
		if (args[0][0] == '-' && !args[0][2])
		{
			return (to_path(1, data));
		}
	}
}
