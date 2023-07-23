/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:13:15 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/24 01:33:48 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_len(char *line)
{
	int	count;
	int	len;
	int	i;

	count = 0;
	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			count++;
		if (line[i] == ')')
			count--;
		if (!count)
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*subshell(char *line)
{
	int	len;
	int	i;

	while (*line && *line != '(')
		if (*line++ != ' ')
			return (NULL);
	len = get_cmd_len(line);
	i = len + 1;
	if (line[len] != ')')
		return (NULL);
	while (line[i])
		if (line[i++] != ' ')
			return (NULL);
	return (ft_substr(line, 1, len - 1));
}

int	detect_brackets(char *cmd)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '(')
			count++;
		if (cmd[i] == ')')
			count--;
		if (count < 0)
			return (-1);
		if (cmd[i] == ')' && count == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	parentheses(char *line, t_sh_data *data)
{
	char	*sub_cmd;
	int		pid;
	int		status;

	sub_cmd = subshell(line);
	if (!sub_cmd)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		exit(WEXITSTATUS(execution_procedure(sub_cmd, data)));
	waitpid(pid, &status, 0);
	free(sub_cmd);
	return (status);
}
