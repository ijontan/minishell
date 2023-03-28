/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:36:24 by itan              #+#    #+#             */
/*   Updated: 2023/03/28 22:05:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
// ! always include stdio.h before readline
// ! otherwise it will cause error
// ! always save without formatting
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

/* --------------------------------- signals -------------------------------- */
void	handle_signal(int signo);

/* ---------------------------------- utils --------------------------------- */
void	free_2d(char **val);
char	**split_args(char *command);

/* ------------------------------- validation ------------------------------- */
char	*check_program_exist(char *program_name, char **envp);

#endif