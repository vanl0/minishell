/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:12:52 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/24 17:12:54 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  has_output(t_simple_cmds *cmd)
{
    t_lexer *redir_i;

    redir_i = cmd->redirections;
    while (redir_i)
    {
        if (redir_i->token == GREAT || redir_i->token == GREATGREAT)
            return (0);
        redir_i = redir_i->next;
    }
    return (1);
}

/* reminder: 
- pipefd[0] is the fd for the read end
- pipefd[1] is the fd for the write end */
static void handle_child(int in_fd, int out_fd, char *path, t_simple_cmds *cmd)
{
    signal(SIGQUIT, handle_sigquit);
    if (in_fd != INVALID_FD)
    { // Redirect input if needed
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }

    if (cmd->redirections)
    {
        heredoc(cmd);
        if (check_redirections(cmd))
            exit(EXIT_FAILURE);
    }

    if (out_fd != INVALID_FD && has_output(cmd))
    { // Redirect output if needed
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
    if (cmd->builtin == NULL)
    {
        unlink(cmd->hd_file_name);
        execv(path, cmd->str);
        exit(EXIT_FAILURE);
    }
    else
        exit(cmd->builtin(cmd));
}

static void handle_parent(int in_fd, int out_fd, t_simple_cmds *cmd)
{
    cmd->pipe_fd[0] = in_fd;
    cmd->pipe_fd[1] = out_fd;
}

void    execute_normal(int in_fd, int out_fd, char *path, t_simple_cmds *cmd)
{
    cmd->child_pid = fork();
    if (cmd->child_pid < 0)
    {   // Error
        free(path);
        perror("fork");
        exit(EXIT_FAILURE); // idk
    }
    if (cmd->child_pid == 0)
        handle_child(in_fd, out_fd, path, cmd);
    else
        handle_parent(in_fd, out_fd, cmd);
}