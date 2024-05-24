#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*writes inside the hidden file using readline till EOF is encountered*/
int do_heredoc(char *hd_file_name,  char *end)
{
    char    *line;
    int     fd;

   
    fd = open(hd_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    line = readline("heredoc>");
    while (line && ft_strncmp(end, line, ft_strlen(end)) && !g_signals.stop_hdoc)
    {
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
        line = readline("heredoc>");
    }
    free(line);
    if (g_signals.stop_hdoc || !line)
        return (FAIL);
    close(fd);
    return (SUCCESS);
}

/*generates a hidden file name used as buffer for heredoc*/
char    *get_hd_name(void)
{
    static int  n = 0;
    char        *num;
    char        *name;

    num = ft_itoa(n);
    name = ft_strjoin("hd_file_", num);
    n++;
    free(num);
    return (name);
}

int heredoc(t_simple_cmds *cmd)
{
    t_lexer *redir_i;

    redir_i = cmd->redirections;
    while (redir_i)
    {
        if (redir_i->token == LESSLESS)
        {
            cmd->hd_file_name = get_hd_name();
            g_signals.in_hdoc = 1;
            do_heredoc(cmd->hd_file_name, redir_i->str);
            g_signals.in_hdoc = 0;
        }
        redir_i = redir_i->next;
    }
    return (SUCCESS);
}