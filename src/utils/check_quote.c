/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:28:51 by itan              #+#    #+#             */
/*   Updated: 2023/08/24 00:29:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_quoted(char *str, int i, int is_quoted)
{
	if ((str[i] == '"' || str[i] == '\'') && !is_quoted)
		is_quoted = str[i];
	else if (str[i] == is_quoted)
		is_quoted = 0;
	return (is_quoted);
}
