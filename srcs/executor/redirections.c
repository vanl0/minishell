#include "minishell.h"

int open_redir(t_lexer *redir)
{
    int fd;

    if (redir->token == GREAT)
    {
        fd = open(redir->str,  O_CREAT | O_RDWR | O_TRUNC, 0644);
    }
    else
    {
        fd = open(redir->str, O_CREAT | O_RDWR | O_APPEND, 0644);
    }
    return (fd);
}

int do_great(t_lexer *redirection)
{
    int fd;

    fd = open_redir(redirection);
    if (fd < 0)
    {
        perror(redirection->str);
        return (EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror(redirection->str);
        return (EXIT_FAILURE);
    }
    close(fd);
    return (EXIT_SUCCESS);
}

int do_less(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror(file);
        return (EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        perror(file);
        return (EXIT_FAILURE);
    }
    close(fd);
    return (EXIT_SUCCESS);
}

/*errors
- < redir file doesnt exist
- > failed to open
*/
int check_redirections(t_simple_cmds *cmd)
{
    t_lexer *redir_i;

    redir_i = cmd->redirections;
    while (redir_i)
    {
        if (redir_i->token == GREAT || redir_i->token == GREATGREAT)
        {
            if (do_great(redir_i))
                return (EXIT_FAILURE);
        }
        if (redir_i->token == LESS)
        {
            if (do_less(redir_i->str))
                return (EXIT_FAILURE);
        }
        if (redir_i->token == LESSLESS)
        {
            if (do_less(cmd->hd_file_name))
                return (EXIT_FAILURE);
        }
        redir_i = redir_i->next;
    }
    return (EXIT_SUCCESS);
}