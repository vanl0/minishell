/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:13:03 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/24 17:13:51 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
/*
this is basically ft_strjoin with a '/' added between the 2 strings */
char	*make_path(char *dir, char *command)
{
	char	*path;
	int		n;
	int		i;
	int		j;

	if (!dir || !command)
		return (NULL);
	n = ft_strlen(dir) + ft_strlen(command) + 2;
	path = malloc(n * sizeof(char));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (dir[++i])
		path[i] = dir[i];
    path[i++] = '/';
    j = -1;
	while (command[++j])
		path[i++] = command[j];
	path[i] = '\0';
	return (path);
}

/* Allocates memory and returns the path to the command executable.
If the command is a builtin, it returns the duplicated command.
If the command is not found, it returns NULL.
*/
char    *find_executable(t_simple_cmds *cmd, char **paths)
{
    int     i;
    char    *command;
    char    *full_path;

    command = cmd->str[0];
    set_builtin(cmd);
    if (access(command, F_OK) == 0 || cmd->builtin != NULL)
    {
        full_path = ft_strdup(command);
        // handle malloc error
        return (full_path);
    }
    i = -1;
    while (paths[++i])
    {
        full_path = make_path(paths[i], command);
        // handle malloc error
        if (access(full_path, F_OK) == 0)
            return (full_path);
        free(full_path);
    }
    return (NULL);
}

// returns exit code of executing cmd (which is the exit code of the child process)
int execute_cmd(t_simple_cmds *cmd, int in_fd, int out_fd)
{
    char    *path;
    int     ret;
    
    ret = EXIT_SUCCESS;
    path = find_executable(cmd, cmd->tools->paths);
    if (!path)
    {
        printf("%s: command not found\n", cmd->str[0]);
        //set error code to 127
        // handle error
        return (EXIT_FAILURE); // idk
    }
    if (cmd->prev || cmd->next || builtin_key(path) == NOT_BUILTIN)
        execute_normal(in_fd, out_fd, path, cmd);
    else
    {
        if (cmd->redirections)
        {
            heredoc(cmd);
            if (check_redirections(cmd))
                exit(EXIT_FAILURE);
        }
        ret = cmd->builtin(cmd);
    }
    free(path);
    return (ret);
}

void    execute_all(t_simple_cmds *cmds)
{
    t_simple_cmds   *tmp;
    int             in_fd;
    int             pipe_fd[2];

    in_fd = INVALID_FD; // For the first command
    tmp = cmds;
    g_signals.in_cmd = 1;
    while (tmp)
    {
        if (tmp->next)
        {
            if (pipe(pipe_fd) == -1)
                return ; // handle pipe error
            execute_cmd(tmp, in_fd, pipe_fd[1]);
            close(pipe_fd[1]);
            if (in_fd != INVALID_FD)
                close(in_fd);
            in_fd = pipe_fd[0];
        }
        else
            execute_cmd(tmp, in_fd, INVALID_FD);
        tmp = tmp->next;
    }
}
