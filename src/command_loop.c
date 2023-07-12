/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/07/12 22:38:11 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh_data(t_sh_data *data, char **env)
{
	data->env = dup_2d(env);
	data->pipes = NULL;
	data->prompt = NULL;
}

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

static void	execution_procedure(char *line, t_sh_data *data)
{
	t_command_chunk	*chunks;
	int				i;
	int				status;

	status = 0;
	chunks = split_command_chunks(line, (char *[]){"&&", "||", NULL});
	i = -1;
	while (chunks[++i].chunk)
		chunks[i].commands = setup_commands(chunks[i].chunk);
	i = -1;
	while (chunks[++i].chunk)
	{
		exec_commands(data, &chunks[i], &status);
		if (chunks[i].sep == NULL)
			break ;
		if (status != 0 && ft_strcmp(chunks[i].sep, "&&") != 0)
			continue ;
		if (status == 0 && ft_strcmp(chunks[i].sep, "||") != 0)
			continue ;
		++i;
	}
	free_t_chunk_array(chunks);
}

void	command_loop(char **env)
{
	t_sh_data	data;
	char		*line;

	init_sh_data(&data, env);
	init_signal();
	setup_signal();
	while (1)
	{
		line = prompt(&data);
		if (line && *line)
			add_history(line);
		if (!line)
			break ;
		if (!*line)
			continue ;
		execution_procedure(line, &data);
		free(line);
	}
	free_2d(data.env);
}
