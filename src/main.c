/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:52:12 by itan              #+#    #+#             */
/*   Updated: 2023/03/28 01:47:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*command_path;
	char	*line;

	(void)ac;
	(void)av;
	command_path = check_program_exist("lsasd", env);
	if (command_path)
		printf("%s\n", command_path);
	else
		printf("command not found\n");
	line = readline("minishell> ");
	printf("%s\n", line);
	return (0);
}
