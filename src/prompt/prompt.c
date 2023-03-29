/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:41:23 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 19:23:52 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

static char	*get_gitbranch(char **env)
{
	int		pipes[2];
	pid_t	pid;
	char	**argv;
	char	*branch;
	char	*tmp;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		close(2);
		tmp = check_program_exist("git", env);
		argv = ft_split("git branch --show-current", ' ');
		execve(tmp, argv, env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(pipes[1]);
	branch = NULL;
	tmp = get_next_line(pipes[0]);
	while (tmp)
	{
		branch = ft_append(branch, tmp);
		free(tmp);
		tmp = get_next_line(pipes[0]);
	}
	tmp = ft_strtrim(branch, "\n");
	free(branch);
	close(pipes[0]);
	return (tmp);
}

static char	*get_hostname(char **env)
{
	int		pipes[2];
	pid_t	pid;
	char	**argv;
	char	*hostname;
	char	*tmp;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		tmp = check_program_exist("hostname", env);
		argv = ft_split(tmp, ' ');
		execve(tmp, argv, env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(pipes[1]);
	hostname = NULL;
	tmp = get_next_line(pipes[0]);
	while (tmp)
	{
		hostname = ft_append(hostname, tmp);
		free(tmp);
		tmp = get_next_line(pipes[0]);
	}
	tmp = ft_strtrim(hostname, ".42kl.edu.my\n");
	free(hostname);
	close(pipes[0]);
	return (tmp);
}

void	get_prompt_data(t_sh_data *sh_data)
{
	sh_data->prompt = ft_calloc(1, sizeof(t_prompt));
	sh_data->prompt->user = getenv("USER");
	sh_data->prompt->hostname = get_hostname(sh_data->env);
	sh_data->prompt->pwd = get_current_dir();
	sh_data->prompt->home = getenv("HOME");
	sh_data->prompt->git_branch = get_gitbranch(sh_data->env);
}

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
	dst = ft_append(dst, "→   ");
	dst = ft_append(dst, RESET);
	return (dst);
}

void	free_prompt_data(t_prompt *prompt)
{
	free(prompt->user);
	free(prompt->hostname);
	free(prompt->pwd);
	free(prompt->home);
	free(prompt);
}
