/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:13:15 by nwai-kea          #+#    #+#             */
/*   Updated: 2023/07/23 01:22:55 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_len(char *line, int i)
{
	int	count;
	int	len;

	count = 0;
	len = 0;
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

char	*subshell(char *line, int i)
{
	char	*sub_cmd;
	int		len;

	len = get_cmd_len(line, i);
	sub_cmd = (char *)malloc(len * sizeof(char));
	ft_strlcpy(sub_cmd, &line[i + 1], len);
	return (sub_cmd);
}

int	detect_brackets(char *cmd)
{
	int		count;
	int		i;

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

char	*parentheses(char *line)
{
	int		i;
	char	*cmd;
	// pid_t	pid;

	// char	**comm;
	cmd = NULL;
	if (detect_brackets(line) < 0)
	{
		perror("incomplete parentheses");
		return (NULL);
	}
	else
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '(')
				cmd = subshell(line, i);
			i++;
		}
		// pid = fork();
		// if (pid == 0)
		// {
		// }
	}
	return (cmd);
}
