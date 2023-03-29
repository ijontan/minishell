/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:36:24 by itan              #+#    #+#             */
/*   Updated: 2023/03/29 04:02:17 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
// this is use to stop stdio.h from moving down when i save
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_prompt
{
	char		*user;
	char		*hostname;
	char		*pwd;
	char		*home;
	int			status;
}				t_prompt;

typedef struct s_sh_data
{
	t_prompt	*prompt;
}				t_sh_data;

/* --------------------------------- prompt --------------------------------- */
void			get_prompt_data(t_sh_data *sh_data);
char			*get_prompt(t_sh_data *sh_data);
void			free_prompt_data(t_prompt *prompt);

/* --------------------------------- signals -------------------------------- */
void			handle_signal(int signo);

/* ---------------------------------- utils --------------------------------- */
char			**dup_2d(char **args);
void			free_2d(char **val);
char			**split_args(char *command);

/* ------------------------------- validation ------------------------------- */
char			*check_program_exist(char *program_name, char **envp);

#endif
