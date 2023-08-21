/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:43:16 by itan              #+#    #+#             */
/*   Updated: 2023/08/22 02:07:09 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *eof, int fd[2])
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (tmp && ft_strcmp(tmp, eof) == 0)
			break ;
		else if (!tmp)
		{
			ft_printf("minishell: warning: heredoc delimited by eof\n");
			exit(1);
		}
		else
		{
			ft_putstr_fd(tmp, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
	}
	exit(1);
}

void	exec_heredoc(t_command *cmd, char *eof, t_sh_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (!eof || !*eof)
	{
		cmd->error = 1;
		return ;
	}
	if (pipe(fd) == -1)
		return ;
	if (cmd->latest_heredoc != -1)
		close(cmd->latest_heredoc);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc(eof, fd);
	}
	waitpid(pid, &(data->status), 0);
	setup_signal();
	close(fd[1]);
	cmd->latest_heredoc = fd[0];
}
