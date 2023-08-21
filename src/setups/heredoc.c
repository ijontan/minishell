/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:43:16 by itan              #+#    #+#             */
/*   Updated: 2023/08/22 00:40:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc(char *eof, t_sh_data *data)
{
	char	*dst;
	char	*tmp;

	dst = 0;
	while (1)
	{
		tmp = readline("> ");
		if (tmp && ft_strcmp(tmp, eof) == 0)
			break ;
		else
		{
			tmp = ft_append(tmp, "\n");
			dst = ft_append(dst, tmp);
			free(tmp);
		}
	}
	free(tmp);
	tmp = dst;
	if (!dst)
		return (dst);
	dst = env_expension_len(dst, data);
	free(tmp);
	return (dst);
}

void	exec_heredoc(t_command *cmd, char *eof, t_sh_data *data)
{
	int		fd[2];
	char	*tmp;

	if (!eof || !*eof)
	{
		cmd->error = 1;
		return ;
	}
	if (pipe(fd) == -1)
		return ;
	if (cmd->latest_heredoc != -1)
		close(cmd->latest_heredoc);
	tmp = heredoc(eof, data);
	if (tmp)
	{
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(fd[1]);
	cmd->latest_heredoc = fd[0];
}
