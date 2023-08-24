/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_command_io.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 19:41:25 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expend_check(char **arg, t_command *cmd, t_sh_data *data)
{
	char	*tmp;
	char	*tmp2;

	tmp = *arg;
	*arg = env_expension(*arg, data);
	tmp2 = *arg;
	*arg = remove_quote(*arg, cmd);
	free(tmp2);
	tmp2 = *arg;
	*arg = wildcard(*arg, data);
	free(tmp2);
	if (countchr(*arg, ' ') > countchr(tmp, ' '))
		cmd->error = AMBIGUOUS_REDIRECT;
	free(tmp);
}

static int	left_arrow(t_command *cmd, int i, t_sh_data *data)
{
	if (cmd->args[i][0] != '<')
		return (0);
	if (!cmd->args[i + 1] || cmd->args[i + 1][0] == '\0')
	{
		cmd->error = SYNTAX_ERROR;
		return (1);
	}
	if (cmd->args[i][1] == '<' && cmd->args[i][2] == '\0')
		cmd->fd_in = cmd->latest_heredoc;
	else if (cmd->args[i][1] == '\0')
	{
		expend_check(&(cmd->args[i + 1]), cmd, data);
		if (cmd->fd_in != 0 && cmd->fd_in != cmd->latest_heredoc)
			close(cmd->fd_in);
		if (!cmd->args[i + 1] || cmd->error == AMBIGUOUS_REDIRECT)
			return (1);
		cmd->fd_in = open(cmd->args[i + 1], O_RDONLY);
		if (cmd->fd_in == -1)
			cmd->error = NO_SUCH_FILE;
	}
	return (2);
}

static int	right_arrow(t_command *cmd, int i, t_sh_data *data)
{
	if (cmd->args[i][0] != '>')
		return (0);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (!cmd->args[i + 1] || cmd->args[i + 1][0] == '\0')
	{
		cmd->error = SYNTAX_ERROR;
		return (1);
	}
	expend_check(&(cmd->args[i + 1]), cmd, data);
	if (!cmd->args[i + 1] || cmd->error == AMBIGUOUS_REDIRECT)
		return (1);
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
				cmd->error = NO_INPUT_FILE;
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
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (cmd->args[++i])
	{
		num += left_arrow(cmd, i, data);
		num += right_arrow(cmd, i, data);
	}
	remove_redirection(cmd, i - num, i - num + 1);
}
