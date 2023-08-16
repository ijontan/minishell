/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:22:35 by itan              #+#    #+#             */
/*   Updated: 2023/08/16 02:22:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_recurse(char *command, int depth)
{
	char	*str;
	char	**dst;
	int		i;
	int		is_quoted;

	is_quoted = 0;
	while (*command == '|')
		command++;
	if (*command == '"' || *command == '\'')
		is_quoted = *command;
	i = 0;
	while ((command[i] != '|' || is_quoted) && command[i])
		if (command[i++] == is_quoted)
			break ;
	str = ft_substr(command, 0, i);
	while (command[i] && command[i] == '|')
		i++;
	if (!command[i])
		dst = (char **)ft_calloc(depth + 2, sizeof(char *));
	else
		dst = split_recurse(command + i, depth + 1);
	dst[depth] = str;
	return (dst);
}

static char	**split_commands(char *command)
{
	int	i;

	if (!command)
		return (0);
	i = ft_strlen(command) - 1;
	while (i >= 0 && (command[i] == ' ' || command[i] == '|'))
	{
		if (command[i] == '|')
			return (0);
		i--;
	}
	while (*command && (*command == '|' || *command == ' '))
	{
		if (*(command) == '|')
			return (0);
		command++;
	}
	if (!*command)
		return (ft_calloc(1, sizeof(char *)));
	return (split_recurse(command, 0));
}

static void	get_heredoc(t_command *cmd, t_sh_data *data)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '<' && cmd->args[i][1] == '<'
			&& cmd->args[i][2] == 0)
			exec_heredoc(cmd, cmd->args[i + 1], data);
		i++;
	}
}

static void	check_split_error(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->args[++i])
	{
		if (!ft_strcmp(cmd->args[i],
						"SOme RanDom Error COde that wiLL never be used"))
			cmd->error = true;
	}
}

/**
 * @brief Set the up commands object
 *
 * @param command the command string
 * @return t_list* the void pointer in each t_list contains the a t_command
 */
t_list	*setup_commands(char *command, t_sh_data *data)
{
	t_list		*dst;
	char		**args;
	int			i;
	t_command	*cmd_tmp;

	args = split_commands(command);
	if (!args)
		return (0);
	dst = 0;
	i = 0;
	while (args[i])
	{
		cmd_tmp = (t_command *)ft_calloc(1, sizeof(t_command));
		cmd_tmp->fd_in = STDIN_FILENO;
		cmd_tmp->fd_out = STDOUT_FILENO;
		cmd_tmp->latest_heredoc = -1;
		cmd_tmp->args = split_args(args[i++]);
		get_heredoc(cmd_tmp, data);
		ft_lstadd_back(&dst, ft_lstnew(cmd_tmp));
		check_split_error(cmd_tmp);
	}
	free_2d(args);
	return (dst);
}
