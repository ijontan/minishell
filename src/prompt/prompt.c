/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:41:23 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 04:02:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"

void	get_prompt_data(t_sh_data *sh_data)
{
	sh_data->prompt = ft_calloc(1, sizeof(t_prompt));
	sh_data->prompt->user = getenv("USER");
	sh_data->prompt->hostname = getenv("HOSTNAME");
	sh_data->prompt->pwd = getenv("PWD");
	sh_data->prompt->home = getenv("HOME");
}

char	*get_prompt(t_sh_data *sh_data)
{
	char		*dst;
	t_prompt	*prompt_data;
	int			len;
	char		*tmp;

	prompt_data = sh_data->prompt;
	dst = ft_strdup("");
	dst = ft_append(dst, BCYAN);
	dst = ft_append(dst, prompt_data->user);
	dst = ft_append(dst, "@");
	dst = ft_append(dst, prompt_data->hostname);
	len = ft_strlen(prompt_data->home);
	tmp = ft_substr(prompt_data->pwd, len, ft_strlen(prompt_data->pwd) - len);
	dst = ft_append(dst, " (");
	dst = ft_append(dst, BWHITE);
	dst = ft_append(dst, "~");
	dst = ft_append(dst, tmp);
	free(tmp);
	dst = ft_append(dst, BCYAN);
	dst = ft_append(dst, ") → ");
	dst = ft_append(dst, RESET);
	return (dst);
}

void	free_prompt_data(t_prompt *prompt)
{
	free(prompt->user);
	free(prompt->hostname);
	free(prompt->pwd);
	free(prompt->home);
	free(prompt);
}
