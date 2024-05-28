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

int has_output(t_simple_cmds *cmd)
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
void    handle_child(int in_fd, int out_fd, char *path, t_simple_cmds *cmd)
{

    if (cmd->redirections)
    {
        heredoc(cmd);
        if (check_redirections(cmd))
            exit(EXIT_FAILURE);
    }
    signal(SIGQUIT, handle_sigquit);
    if (cmd->builtin == NULL)
    {
        if (in_fd != INVALID_FD)
        { // Redirect input if needed
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != INVALID_FD && has_output(cmd))
        { // Redirect output if needed
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        unlink(cmd->hd_file_name);
        execv(path, cmd->str);
        // if execv fails, handle error.
    }
    else
        exit(cmd->builtin(cmd));
}

void    handle_parent(int in_fd, int out_fd, t_simple_cmds *cmd)
{
    cmd->pipe_fd[0] = in_fd;
    cmd->pipe_fd[1] = out_fd;
}
