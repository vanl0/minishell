/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:30:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/06/06 16:35:33 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# define MAX_PATH 1024
# define SUCCESS 1
# define FAIL 0
# define INVALID_FD -1
# define NO_PID -2

# define QUOTE_ERROR 0
# define SYNTAX_ERROR 1
# define IS_DIRECTORY 126
# define CMD_NOT_FOUND 127
# define FORK_ERROR 3
# define EXECV_ERROR 4
# define SYNTAX_ERR_MSG "minishell: syntax error near unexpected token "
# define USER_DIR "/home"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../readline-8.1/history.h"
# include "../readline-8.1/readline.h"
# include "../libft/libft.h"
# include "parser.h"
# include "lexer.h"
# include "builtins.h"
# include <dirent.h>
# include <limits.h>

typedef struct s_signals
{
	int	exit_stat;
	int	in_cmd;
	int	in_hdoc;
	int	stop_hdoc;
}		t_signals;

extern t_signals	g_signals;

//MINISHELL
int		minishell(t_tools *tools);
int		clean_restart(t_tools *tools);

// EXECUTION UTILS
int		is_directory(char *path);
void	to_lower_loop(char *str);
void	handle_child(int in_fd, int out_fd, char *path, t_simple_cmds *cmd);
void	handle_parent(int in_fd, int out_fd, t_simple_cmds *cmd);

// EXECUTION
void	execute_all(t_simple_cmds *cmd);

//SIGNALS
void	start_signals(void);
void	handle_sigquit(int sig);
void	handle_sigint(int sig);

//ERROR
int		do_error(int flg, t_tools *tools);
#endif
