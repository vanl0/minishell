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
/* Allocates memory and returns the path to the command executable.
If the command is a builtin, it returns the duplicated command.
If the command is not found, it returns NULL.
*/

void    to_lower_loop(char *str)
{
    while (*str)
    {
        ft_tolower(*str);
        str++;
    }
}

char    *find_executable(t_simple_cmds *cmd, char **paths)
{
    int     i;
    char    *command;
    char    *full_path;

    if (!paths)
        return (NULL);
    command = cmd->str[0];
    set_builtin(cmd);
    if (access(command, F_OK) == 0 || cmd->builtin != NULL)
    {
        full_path = ft_strdup(command);
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
    int     og_stdout;
    int     og_stdin;
    
    
    if (!cmd->str[0])
    {
        if (cmd->redirections)
        {
            og_stdout = dup(STDOUT_FILENO);
            og_stdin = dup(STDIN_FILENO);
            heredoc(cmd);
            if (check_redirections(cmd))
            {
                g_signals.exit_stat = EXIT_FAILURE;
                //clean_tools(cmd->tools);
                minishell(cmd->tools);
            }
        }
        if (cmd->redirections)
        {
            dup2(og_stdout, STDOUT_FILENO);
            dup2(og_stdin, STDIN_FILENO);
            close(og_stdout);
            close(og_stdin);
        }
        return (EXIT_SUCCESS);
    }
    path = find_executable(cmd, cmd->tools->paths);
    if (!path)
    {
        ft_putstr_fd(cmd->str[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        //set error code to 127
        g_signals.exit_stat = 127;
        return (127); // idk
    }
    if (cmd->prev || cmd->next || builtin_key(path) == NOT_BUILTIN)
        execute_normal(in_fd, out_fd, path, cmd);
    else
    {
        if (cmd->redirections)
        {
            og_stdout = dup(STDOUT_FILENO);
            og_stdin = dup(STDIN_FILENO);
            heredoc(cmd);
            if (check_redirections(cmd))
            {
                g_signals.exit_stat = EXIT_FAILURE;
                //clean_tools(cmd->tools);
                minishell(cmd->tools);
            }
        }
        g_signals.exit_stat = cmd->builtin(cmd);
        if (cmd->redirections)
        {
            dup2(og_stdout, STDOUT_FILENO);
            dup2(og_stdin, STDIN_FILENO);
            close(og_stdout);
            close(og_stdin);
        }
    }
    free(path);
    return (EXIT_SUCCESS);
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
