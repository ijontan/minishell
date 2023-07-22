/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:46:06 by itan              #+#    #+#             */
/*   Updated: 2023/07/22 14:19:04 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO: implement update to the env variable

/**
 * @brief cd should change the current working directory
 * 
 * @param args place holder parameter for now
 */

static int	update_oldpwd(char **env)
{
	char	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	if (!cwd)
		return (0);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (0);
	if (env_not_exist("OLDPWD", env))
		add_env_var(oldpwd, env);
	else
		overwrite_var(oldpwd, env);
	// ft_memdel(oldpwd);
	return (1);
}

static char	*check_env(char *args, char **env, int j)
{
	int		i;
	int		k;
	int		valuelen;
	char	*add;

	i = 0;
	while (env[i])
	{
		valuelen = ft_strlen(env[i]) - j;
		if (!ft_strncmp(env[i], args, j))
		{
			add = malloc(sizeof(char) * valuelen + 1);
			if (!add)
				return (NULL);
			k = 0;
			j += 1;
			while (env[i][j])
				add[k++] = env[i][j++];
			add[k] = '\0';
			return (add);
		}
		i++;
	}
	return (NULL);
}

static int	to_path(int path, t_sh_data *data)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (path == 0)
	{
		update_oldpwd(data->env);
		env_path = check_env("HOME", data->env, 4);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : HOME not set", STDERR_FILENO);
		if (env_path == NULL)
			return (1);
	}
	else if (path == 1)
	{
		env_path = check_env("OLDPWD", data->env, 6);
		if (env_path == NULL)
			ft_putendl_fd("minishell : cd : OLDPWD not set", STDERR_FILENO);
		if (env_path == NULL)
			return (1);
		update_oldpwd(data->env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	cd(char **args, t_sh_data *data)
{
	int	ret;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (to_path(0, data));
	if (args[2])
	{
		ft_putendl_fd("minishell : cd : too many arguments", STDERR_FILENO);
		return (1);
	}
	if (args[1][0] == '-' && !args[1][1])
		return (to_path(1, data));
	else
	{
		update_oldpwd(data->env);
		ret = chdir(args[1]);
		if (ret != 0)
			perror(args[1]);
		if (ret < 0)
			ret *= -1;
	}
	return (ret);
}
