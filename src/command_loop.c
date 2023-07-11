/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:45:39 by itan              #+#    #+#             */
/*   Updated: 2023/07/11 14:30:40 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_sh_data(t_sh_data *data, char **env)
{
	ss data->env = dup_2d(env);
	data->command_chunks = NULL;
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
	t_list			*chunk;

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
		while (chunks->chunk)
		{
			chunks->commands = setup_commands(chunks->chunk);
			chunk = ft_lstnew(chunks);
			exec_commands(&data, chunk);
			chunks++;
		}
		free_t_chunk_list(&chunk);
		free(line);
	}
}
