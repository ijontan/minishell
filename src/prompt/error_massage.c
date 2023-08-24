/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:44:23 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 18:26:30 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_massage(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

static void	set_error(int error_code, t_sh_data *data)
{
	if (error_code == SYNTAX_ERROR)
		data->status = 2;
	else if (error_code == NO_SUCH_FILE)
		data->status = 1;
	else if (error_code == NO_SUCH_DIR)
		data->status = 1;
	else if (error_code == NO_INPUT_FILE)
		data->status = 1;
	else if (error_code == AMBIGUOUS_REDIRECT)
		data->status = 1;
	else if (error_code == HEREDOC_NOTFOULD)
		data->status = 0;
	else if (error_code == PARSE_ERROR)
		data->status = 2;
}

void	handle_error(t_command *cmd, t_sh_data *data)
{
	int	error_code;

	error_code = cmd->error;
	set_error(error_code, data);
	if (error_code == SYNTAX_ERROR)
		error_massage("Syntax error");
	else if (error_code == NO_SUCH_FILE)
		error_massage("No such file or directory");
	else if (error_code == NO_SUCH_DIR)
		error_massage("No such directory");
	else if (error_code == NO_INPUT_FILE)
		error_massage("No input file");
	else if (error_code == AMBIGUOUS_REDIRECT)
		error_massage("Ambiguous redirect");
	else if (error_code == HEREDOC_NOTFOULD)
		error_massage("heredoc not found");
	else if (error_code == PARSE_ERROR)
		error_massage("Parse error");
}

void	handle_error_chunk(t_sh_data *data)
{
	error_massage("Syntax error");
	set_error(SYNTAX_ERROR, data);
}
