/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:36:24 by itan              #+#    #+#             */
/*   Updated: 2023/04/02 21:52:55 by itan             ###   ########.fr       */
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
	char		*git_branch;
	int			status;
}				t_prompt;

typedef struct s_command
{
	char		*program;
	char		**args;
	int			fd_in;
	int			fd_out;
	char		*here_doc;
}				t_command;

typedef struct s_pipe
{
	int			pipe[2];
}				t_pipe;

typedef struct s_sh_data
{
	t_prompt	*prompt;
	char		**env;
	t_command	*commands;
	t_pipe		*pipes;
}				t_sh_data;

/* -------------------------------- build_in -------------------------------- */
void			cd(char **args);

/* --------------------------------- prompt --------------------------------- */
void			get_prompt_data(t_sh_data *sh_data);
char			*get_prompt(t_sh_data *sh_data);
void			free_prompt_data(t_prompt *prompt);

/* --------------------------------- signals -------------------------------- */
void			handle_signal(int signo);

/* ---------------------------------- utils --------------------------------- */
char			**dup_2d(char **args);
void			free_2d(char **val);
char			*get_current_dir(void);
char			**split_args(char *command);

/* ------------------------------- validation ------------------------------- */
char			*check_program_exist(char *program_name, char **env);

#endif
