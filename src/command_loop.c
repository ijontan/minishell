/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 17:35:31 by itan             ###   ########.fr       */
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

void	command_loop(char **env)
{
	t_sh_data		data;
	char			*line;
	t_command_chunk	*chunks;
	int				i;

	init_sh_data(&data, env);
	setup_signal();
	while (1)
	{
		line = prompt(&data);
		if (line && *line)
			add_history(line);
		if (!line)
		{
			ft_printf("\n");
			break ;
		}
		if (!*line)
			continue ;
		chunks = split_command_chunks(line, (char *[]){"&&", "||", NULL});
		i = -1;
		while (chunks[++i].chunk)
		{
			chunks->commands = setup_commands(chunks->chunk);
			exec_commands(&data, &chunks[i]);
		}
		free_t_chunk_array(chunks);
		free(line);
	}
}
