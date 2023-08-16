/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_command_io.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/08/14 00:56:32 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	left_arrow(t_command *cmd, int i, t_sh_data *data)
{
	char	*tmp;

	if (cmd->args[i][0] != '<')
		return (0);
	if (!cmd->args[i + 1] || cmd->args[i + 1][0] == '\0')
	{
		cmd->error = 1;
		return (1);
	}
	if (cmd->args[i][1] == '<' && cmd->args[i][2] == '\0')
		cmd->fd_in = cmd->latest_heredoc;
	else if (cmd->args[i][1] == '\0')
	{
		tmp = cmd->args[i + 1];
		cmd->args[i + 1] = env_expension(cmd->args[i + 1], data);
		free(tmp);
		if (cmd->fd_in != 0 && cmd->fd_in != cmd->latest_heredoc)
			close(cmd->fd_in);
		if (!cmd->args[i + 1])
			return (1);
		cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
		if (cmd->fd_in == -1)
			cmd->error = 1;
	}
	return (2);
}

static int	right_arrow(t_command *cmd, int i, t_sh_data *data)
{
	char	*tmp;

	if (cmd->args[i][0] != '>')
		return (0);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (!cmd->args[i + 1] || cmd->args[i + 1][0] == '\0')
	{
		cmd->error = 1;
		return (1);
	}
	tmp = cmd->args[i + 1];
	cmd->args[i + 1] = env_expension(cmd->args[i + 1], data);
	free(tmp);
	if (cmd->args[i][1] == '>' && cmd->args[i][2] == '\0')
		cmd->fd_out = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	else if (cmd->args[i][1] == '\0')
		cmd->fd_out = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	return (2);
}

static void	remove_redirection(t_command *cmd, int num, int size)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = (char **)ft_calloc(size, sizeof(char *));
	i = -1;
	j = 0;
	while (++i < num)
	{
		if (cmd->args[j] && (cmd->args[j][0] == '<' || cmd->args[j][0] == '>'))
		{
			j++;
			if (cmd->args[j])
				j++;
			else
				cmd->error = 1;
		}
		if (cmd->args[j])
			tmp[i] = ft_strdup(cmd->args[j++]);
	}
	free_2d(cmd->args);
	cmd->args = tmp;
}

/**
 * @brief This function will sanitize the command io and remove redirections,
 * also open the files for the command
 * @param cmd
 */
void	sanitize_command_io(t_command *cmd, t_sh_data *data)
{
	int		i;
	int		num;
	char	*tmp;

	i = -1;
	num = 0;
	while (cmd->args[++i])
	{
		num += left_arrow(cmd, i, data);
		num += right_arrow(cmd, i, data);
	}
	remove_redirection(cmd, i - num, i - num + 1);
	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i] && ft_strchr(cmd->args[i], '*'))
		{
			tmp = cmd->args[i];
			cmd->args[i] = wildcard(tmp, data);
			free(tmp);
		}
	}
	split_expand(&(cmd->args));
}
