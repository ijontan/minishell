/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:41:23 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 14:28:18 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

// TODO: should be updated
/**
 * @brief Get the git branch name
 *
 * @param env
 * @return char*
 */
static char	*get_gitbranch(char **env)
{
	char	*branch;
	char	*tmp;

	branch = prompt_exec(env, "git branch --show-current");
	tmp = ft_strtrim(branch, "\n");
	free(branch);
	return (tmp);
}

// TODO: should be updated
/**
 * @brief Get the hostname of the computer, for now
 *
 * @param env
 * @return char*
 */
static char	*get_hostname(char **env)
{
	char	*hostname;
	char	*tmp;

	hostname = prompt_exec(env, "hostname");
	tmp = ft_strtrim(hostname, ".42kl.edu.my\n");
	free(hostname);
	return (tmp);
}

/**
 * @brief update the prompt data
 *
 * @param sh_data minishell data
 */
void	get_prompt_data(t_sh_data *sh_data)
{
	sh_data->prompt = ft_calloc(1, sizeof(t_prompt));
	sh_data->prompt->user = getenv("USER");
	sh_data->prompt->hostname = get_hostname(sh_data->env);
	sh_data->prompt->pwd = get_current_dir();
	sh_data->prompt->home = getenv("HOME");
	sh_data->prompt->git_branch = get_gitbranch(sh_data->env);
}

/**
 * @brief Get the prompt string from the prompt data
 *
 * @param sh_data minishell data
 * @return char*
 */
char	*get_prompt(t_sh_data *sh_data)
{
	char		*dst;
	t_prompt	*prompt_data;

	prompt_data = sh_data->prompt;
	dst = ft_strdup("");
	dst = ft_append(dst, BCYAN);
	dst = ft_append(dst, prompt_data->user);
	dst = ft_append(dst, "@");
	dst = ft_append(dst, prompt_data->hostname);
	dst = ft_append(dst, " (");
	dst = ft_append(dst, BWHITE);
	dst = ft_append(dst, prompt_data->pwd);
	dst = ft_append(dst, BCYAN);
	dst = ft_append(dst, ") ");
	if (sh_data->prompt->git_branch)
	{
		dst = ft_append(dst, BRED);
		dst = ft_append(dst, "⌥ ");
		dst = ft_append(dst, prompt_data->git_branch);
		dst = ft_append(dst, " ");
		dst = ft_append(dst, RESET);
	}
	dst = ft_append(dst, "→  ");
	dst = ft_append(dst, RESET);
	return (dst);
}

/**
 * @brief Free prompt data
 *
 * @param prompt the prompt data
 */
void	free_prompt_data(t_prompt *prompt)
{
	free(prompt->hostname);
	free(prompt->pwd);
	free(prompt->git_branch);
	free(prompt);
}
