/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:36:24 by itan              #+#    #+#             */
/*   Updated: 2023/07/10 19:02:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
// this is use to stop stdio.h from moving down when i save
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

/**
 * @brief data for prompt
 *
 * @param user username
 * @param hostname hostname
 * @param pwd current working directory
 * @param home home directory
 * @param git_branch git branch name
 * @param status exit status of last command
 */
typedef struct s_prompt
{
	char		*user;
	char		*hostname;
	char		*pwd;
	char		*home;
	char		*git_branch;
	int			status;
}				t_prompt;

/**
 * @brief chunk of commands separated by && or || or parentheses
 *
 * @param chunk the string of commands
 * @param sep the separator between this chunk and the next chunk
 */
typedef struct s_command_chunk
{
	char		*chunk;
	char		*sep;
	t_list		*commands;
}				t_command_chunk;

/**
 * @brief required datas for a single command
 *
 * @param program program name eg. ls, echo
 * @param args arguments for program including program name
 * @param fd_in file descriptor for input
 * @param fd_out file descriptor for output
 */
typedef struct s_command
{
	char		*program;
	char		**args;
	int			fd_in;
	int			fd_out;
	int			latest_heredoc;
}				t_command;

typedef struct s_pipe
{
	int			pipe[2];
}				t_pipe;

/**
 * @brief required datas for shell
 *
 * @param prompt prompt data
 * @param env environment variables
 * @param command_chunks linked list for t_command_chunk
 * @param pipes linked list for t_pipe
 */
typedef struct s_sh_data
{
	t_prompt	*prompt;
	char		**env;
	t_list		*command_chunks;
	t_list		*pipes;
}				t_sh_data;

void			command_loop(char **env);

/* -------------------------------- build_in -------------------------------- */

void			cd(char **args);

/* ---------------------------------- exec ---------------------------------- */

void			exec_commands(t_sh_data *sh_data, t_list *command_chunk);
void			sanitize_command_io(t_command *cmd);
/* --------------------------------- prompt --------------------------------- */

void			get_prompt_data(t_sh_data *sh_data);
char			*get_prompt(t_sh_data *sh_data);
void			free_prompt_data(t_prompt *prompt);

/* ---------------------------------- setup --------------------------------- */
char			**split_expand(char **args, char sep);
char			*env_expension(char *arg, char **env);
char			*heredoc(char *eof);
void			exec_heredoc(t_command *cmd, char *eof);
t_list			*setup_commands(char *command);

/* --------------------------------- signals -------------------------------- */

void			handle_signal(int signo);
void			setup_signal(void);

/* ------------------------------ tokenization ------------------------------ */

char			*expand_env(char *str, char **env);
t_list			*tokenize(char *command);
/* ---------------------------------- utils --------------------------------- */

char			**dup_2d(char **args);
void			free_2d(char **val);
char			*get_current_dir(void);
char			*get_env(char **envp, char *name);
char			**split_args(char *command);
t_command_chunk	*split_command_chunks(char *str, char **seps);
/* ------------------------------- validation ------------------------------- */

char			*check_program_exist(char *program_name, char **env);

#endif
