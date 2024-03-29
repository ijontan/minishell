/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 18:26:47 by itan             ###   ########.fr       */
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

static t_command_chunk	*setup_chunk(char *line, t_sh_data *data)
{
	int				i;
	bool			err;
	t_command_chunk	*chunks;

	err = false;
	chunks = split_command_chunks(line, (char *[]){"&&", "||", NULL});
	if (!chunks)
		err = true;
	i = -1;
	while (!err && chunks[++i].chunk)
	{
		if (!chunks[i].is_subshell)
			chunks[i].commands = setup_commands(chunks[i].chunk, data);
		if (!chunks[i].commands)
			chunks[i].error = 1;
		if (!chunks[i + 1].chunk && chunks[i].sep)
			err = true;
	}
	if (err)
	{
		handle_error_chunk(data);
		free_t_chunk_array(chunks);
		return (NULL);
	}
	return (chunks);
}

static bool	check_continue(t_command_chunk *chunk, t_sh_data *data)
{
	if ((data->status == 0 && !chunk->error) && ft_strcmp(chunk->sep,
			"&&") == 0)
		return (true);
	if ((data->status != 0 || chunk->error) && ft_strcmp(chunk->sep, "||") == 0)
		return (true);
	return (false);
}

int	execution_procedure(char *line, t_sh_data *data)
{
	t_command_chunk	*chunks;
	int				i;

	chunks = setup_chunk(line, data);
	if (!chunks)
		return (1);
	i = -1;
	while (chunks[++i].chunk)
	{
		if (chunks[i].is_subshell)
			parentheses(chunks[i].chunk, data);
		else
			exec_commands(data, &chunks[i]);
		if (chunks[i].sep == NULL)
			break ;
		if (check_continue(&chunks[i], data))
			continue ;
		++i;
	}
	free_t_chunk_array(chunks);
	return (data->status);
}

void	command_loop(char **env)
{
	t_sh_data	data;
	char		*line;

	data.env = dup_2d(env);
	data.pipes = NULL;
	data.prompt = NULL;
	init_signal();
	shlvl(&data);
	while (!g_sig.sigquit)
	{
		setup_signal();
		line = prompt(&data);
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		if (*line)
			execution_procedure(line, &data);
		free(line);
	}
	clear_history();
	free_2d(data.env);
}
