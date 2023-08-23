/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:44:23 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 01:02:51 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_massage(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_error(int error_code)
{
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
