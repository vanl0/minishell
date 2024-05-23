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
        check_redirections(cmd);
    }
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
    execv(path, cmd->str);
    // if execv fails, handle error.
}

int handle_parent(int in_fd, int out_fd, pid_t child_pid)
{
    int     status;

    if (in_fd != INVALID_FD)
        close(in_fd);
    if (out_fd != INVALID_FD)
        close(out_fd);
    waitpid(child_pid, &status, 0);
    return (WIFEXITED(status));
}
