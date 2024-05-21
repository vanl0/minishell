#include "minishell.h"

/* reminder: 
- pipefd[0] is the fd for the read end
- pipefd[1] is the fd for the write end */
void    handle_child(int pipefd[2], int in_fd, t_simple_cmds *cmd)
{
    if (in_fd != STDIN_FILENO)
    {
        printf("[Child] Redirecting input from file descriptor %d to STDIN\n", in_fd);
        dup2(in_fd, STDIN_FILENO); // Redirect in_fd to STDIN
        close(in_fd); // since it is now open in STDIN
    }
    if (cmd->prev && pipefd)
    {
        printf("[Child] Closing read end of the pipe (%d) in the child\n", pipefd[0]);
        close(pipefd[0]); // because read end is useless if we are in child
        printf("[Child] Redirecting output to file descriptor %d (STDIN)\n", pipefd[1]);
        dup2(pipefd[1], STDOUT_FILENO); // Redirect write end to STDIN
        close(pipefd[1]); // since it is now open in STDOUT
    }
}

void    handle_parent(int pipefd[2], int *in_fd, t_simple_cmds *cmd)
{
    if (*in_fd != STDIN_FILENO) // check needed to never close STDIN
    {
        printf("[Parent] Closing file descriptor %d (input)\n", *in_fd);
        close(*in_fd);
    }
    if (cmd->next && pipefd)
    {
        printf("[Parent] Closing write end of the pipe (%d)\n", pipefd[1]);
        close(pipefd[1]); // because write end is useless in parent
        printf("[Parent] Updating input file descriptor to read end of the pipe (%d)\n", pipefd[0]);
        *in_fd = pipefd[0]; // update in_fd to read end
    }
}