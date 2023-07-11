/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:35:44 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 13:56:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_exec(char **env, char *command)
{
	int		pipes[2];
	pid_t	pid;
	char	*tmp;
	char	**argv;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		close(2);
		argv = ft_split(command, ' ');
		tmp = check_program_exist(argv[0], env);
		execve(tmp, argv, env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(pipes[1]);
	tmp = get_next_line(pipes[0]);
	close(pipes[0]);
	return (tmp);
}
