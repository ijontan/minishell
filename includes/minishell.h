/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwai-kea <nwai-kea@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:36:24 by itan              #+#    #+#             */
/*   Updated: 2023/07/18 17:17:10 by nwai-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
// this is use to stop stdio.h from moving down when i save
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define STDERR 2

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
	bool		subshell;
	int			count;
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
 * @param exited exit status
 */
typedef struct s_sh_data
{
	t_prompt	*prompt;
	char		**env;
	t_list		*pipes;
	DIR			*dir;
	int			exited;
	int			status;
}				t_sh_data;

typedef struct s_sig
{
	int			sigint;
	int			sigstatus;
	int			sigquit;
	pid_t		pid;
}				t_sig;

extern t_sig	g_sig;

void			command_loop(char **env);

/* -------------------------------- build_in -------------------------------- */

void			add_env_var(char *args, char **env);
int				cd(char **args, t_sh_data *data);
int				echo(char **args);
int				env_not_exist(char *args, char **env);
int				env(char **args, char **env);
int				exit_buildin(t_sh_data *data, char **args);
void			overwrite_var(char *args, char **env);
int				export(char **args, char **env);
int				pwd(void);
int				unset(char **args, char **env);

/* ----------------------------------- env ---------------------------------- */
void			*ft_memdel(void *ptr);
int				len_till_equal(char *str);
int				ft_strstart(char *s1, char *s2);
int				find_env_pos(char *args, char **env);
void			sort_env(char **env);
int				env_valid(char *env);

/* ---------------------------------- exec ---------------------------------- */
int				exec_builtin(char **args, t_sh_data *data);
void			exec_commands(t_sh_data *sh_data, t_command_chunk *chunk,
					int *status);
void			sanitize_command_io(t_command *cmd);
/* --------------------------------- prompt --------------------------------- */

void			get_prompt_data(t_sh_data *sh_data);
char			*get_prompt(t_sh_data *sh_data);
void			free_prompt_data(t_prompt *prompt);
char			*prompt_exec(char **env, char *command);

/* ---------------------------------- setup --------------------------------- */
void			expand_all_args(char **args, t_sh_data *data);
char			**split_expand(char **args, char sep);
char			*env_expension(char *arg, char **env);
void			wildcard(char *arg, t_sh_data *data);
char			*heredoc(char *eof);
void			exec_heredoc(t_command *cmd, char *eof);
t_list			*setup_commands(char *command);

/* --------------------------------- signals -------------------------------- */

void			init_signal(void);
void			handle_signal(int signo);
void			handle_signal_quit(int signo);
void			setup_signal(void);

/* ---------------------------------- utils --------------------------------- */

char			**dup_2d(char **args);
void			free_2d(char **val);
void			free_t_chunk_array(t_command_chunk *command_chunks);
char			*get_current_dir(void);
char			*get_env(char **envp, char *name);
char			**split_args(char *command);
t_command_chunk	*split_command_chunks(char *str, char **seps);
/* ------------------------------- validation ------------------------------- */

char			*check_program_exist(char *program_name, char **env);

#endif
