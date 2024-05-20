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
        perror("minishell :");
        return (FAIL);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell :");
        return (FAIL);
    }
    return (SUCCESS);
}

int do_less(t_lexer *redirections)
{
    int fd;

    fd = open(redirections->str, O_RDONLY);
    if (fd < 0)
    {
        perror("minishell :");
        return (FAIL);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        perror("minishell :");
        return (FAIL);
    }
    close(fd);
    return (SUCCESS);
}

int check_redirections(t_lexer *redirections)
{
    t_lexer *redir_i;

    redir_i = redirections;
    while (redir_i)
    {
        if (redir_i->token == GREAT || redir_i->token == GREATGREAT)
        {
            if (!do_great(redir_i))
                return (FAIL);
        }
        if (redir_i->token == LESS)
        {
            if (!do_less(redir_i))
                return (FAIL);
        }
        if (redir_i->token == LESSLESS)
        {
            
        }
        redir_i = redir_i->next;
    }
    return (SUCCESS);
}