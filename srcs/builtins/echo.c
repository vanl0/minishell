#include "minishell.h"

void    print_echo(char **str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        

    }
}

int echo(t_tools *tools, t_simple_cmds *simple_cmd)
{
    int     n_flag;
    int     i;
    int     j;
    char    **str;

    i = 1;
    n_flag = 0;
    str = simple_cmd->str;
    while (str[i] && str[i][0] == '-' && str[i][1] == 'n')
    {
        j = 1;
        while (str[i][j] == 'n')
            j++;
        if (str[i][j] == '\0')
            n_flag = 1;
        else
            break;
        i++;
    }
    


    return (0);
}