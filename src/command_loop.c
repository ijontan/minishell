/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/07/24 01:29:00 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt(t_sh_data *data)
{
	char	*prompt_str;
	char	*dst;

	get_prompt_data(data);
	prompt_str = get_prompt(data);
	free_prompt_data(data->prompt);
	dst = readline(prompt_str);
	free(prompt_str);
	return (dst);
}

static t_command_chunk	*setup_chunk(char *line)
{
	int				i;
	t_command_chunk	*chunks;

	chunks = split_command_chunks(line, (char *[]){"&&", "||", NULL});
	if (!chunks)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		return (NULL);
	}
	i = -1;
	while (chunks[++i].chunk)
		if (!chunks[i].is_subshell)
			chunks[i].commands = setup_commands(chunks[i].chunk);
	return (chunks);
}

static bool	check_continue(t_command_chunk *chunk, int status)
{
	if (status != 0 && ft_strcmp(chunk->sep, "&&") != 0)
		return (true);
	if (status == 0 && ft_strcmp(chunk->sep, "||") != 0)
		return (true);
	return (false);
}

int	execution_procedure(char *line, t_sh_data *data)
{
	t_command_chunk	*chunks;
	int				i;
	int				status;

	status = 0;
	chunks = setup_chunk(line);
	if (!chunks)
		return (1);
	i = -1;
	while (chunks[++i].chunk)
	{
		if (chunks[i].is_subshell)
			status = parentheses(chunks[i].chunk, data);
		else
			exec_commands(data, &chunks[i], &status);
		data->status = WEXITSTATUS(status);
		if (chunks[i].sep == NULL)
			break ;
		if (check_continue(&chunks[i], status))
			continue ;
		++i;
	}
	free_t_chunk_array(chunks);
	return (status);
}

void	command_loop(char **env)
{
	t_sh_data	data;
	char		*line;

	data.env = dup_2d(env);
	data.pipes = NULL;
	data.prompt = NULL;
	init_signal();
	setup_signal();
	while (1)
	{
		line = prompt(&data);
		if (line && *line)
			add_history(line);
		if (!line || g_sig.sigquit)
			break ;
		if (!*line)
			continue ;
		execution_procedure(line, &data);
		free(line);
	}
	free_2d(data.env);
}
