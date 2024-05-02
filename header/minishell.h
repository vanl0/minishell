/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:31:13 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/04/30 16:31:14 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>     // printf
#include <stdlib.h>    // malloc, free, exit
#include <unistd.h>    // write, access, fork, execve, close, chdir
#include <fcntl.h>     // open
#include <sys/wait.h>  // wait, waitpid, wait3, wait4
#include <signal.h>    // signal, sigaction, kill
#include <string.h>    // strerror
#include <errno.h>     // perror
#include <sys/types.h> // stat, lstat, fstat, unlink, opendir, readdir, closedir
#include <sys/stat.h>  // stat, lstat, fstat
#include <dirent.h>    // opendir, readdir, closedir
#include <termios.h>   // tcsetattr, tcgetattr
#include <sys/ioctl.h> // ioctl
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ttydefaults.h> // isatty, ttyname, ttyslot
#include <termcap.h>   // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


#endif