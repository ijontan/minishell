/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:43:16 by itan              #+#    #+#             */
/*   Updated: 2023/06/26 15:45:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc(char *eof)
{
	char	*dst;

	while (1)
	{
		dst = readline("> ");
		if (ft_strcmp(dst, eof) == 0)
			break ;
		else
			ft_append(dst, "\n");
	}
	return (dst);
}
