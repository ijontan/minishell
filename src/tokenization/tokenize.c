/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:42:38 by itan              #+#    #+#             */
/*   Updated: 2023/06/22 16:15:03 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: add env expansion to this function
// TODO: add redirection to this function
// TODO: add heredoc to this function

/**
 * @brief Split the input string into command blocks
 *
 * @param args The string to split
 * @return t_command* The array of command blocks
 */
t_list	*tokenize(char *command)
{
	t_list		*dst;
	char		**args;
	int			i;
	t_command	*cmd_tmp;

	args = ft_split(command, '|');
	dst = 0;
	i = 0;
	while (args[i])
	{
		cmd_tmp = (t_command *)ft_calloc(1, sizeof(t_command));
		cmd_tmp->args = split_args(args[i++]);
		ft_lstadd_back(&dst, ft_lstnew(cmd_tmp));
	}
	return (dst);
}
