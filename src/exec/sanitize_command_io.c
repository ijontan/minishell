/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_command_io.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/06/28 21:31:34 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	left_arrow(t_command *cmd, int i)
{
	if (cmd->args[i][0] == '<')
	{
		if (cmd->args[i][1] == '<')
			cmd->fd_in = HEREDOC_NUM;
		else
		{
			if (cmd->fd_in != 0 && cmd->fd_in != HEREDOC_NUM)
				close(cmd->fd_in);
			if (!cmd->args[i + 1])
				return (1);
			cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
		}
		return (1);
	}
	return (0);
}

static int	right_arrow(t_command *cmd, int i)
{
	if (cmd->args[i][0] == '>')
	{
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		if (cmd->args[i][1] == '>')
			cmd->fd_out = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			cmd->fd_out = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		return (1);
	}
	return (0);
}

/**
 * @brief This function will sanitize the command io and remove redirections,
 * also open the files for the command
 * @param cmd 
 */
void	sanitize_command_io(t_command *cmd)
{
	int		i;
	int		j;
	int		num;
	char	**tmp;

	i = -1;
	num = 0;
	while (cmd->args[++i])
	{
		num += left_arrow(cmd, i);
		num += right_arrow(cmd, i);
	}
	tmp = (char **)ft_calloc(i - num, sizeof(char *));
	num = i - num * 2;
	i = -1;
	j = 0;
	while (++i < num)
	{
		if (cmd->args[j] && (cmd->args[j][0] == '<' || cmd->args[j][0] == '>'))
			j += 2;
		tmp[i] = ft_strdup(cmd->args[j++]);
	}
	free_2d(cmd->args);
	cmd->args = tmp;
}
