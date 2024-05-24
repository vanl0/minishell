#include "minishell.h"

/* Returns the command's builtin key. -1 if not a builtin. */
int builtin_key(char *command)
{
    if (ft_strncmp(command, "echo", 5))
        return (ECHO);
    if (ft_strncmp(command, "cd", 3))
        return (CD);
    if (ft_strncmp(command, "pwd", 4))
        return (PWD);
    if (ft_strncmp(command, "export", 7))
        return (EXPORT);
    if (ft_strncmp(command, "unset", 6))
        return (UNSET);
    if (ft_strncmp(command, "env", 4))
        return (ENV);
    if (ft_strncmp(command, "exit", 5))
        return (EXIT);
    return (NOT_BUILTIN);
}

int (*return_builtin(int key))(t_tools *tools, t_simple_cmds *cmd)
{
    void    *builtin_array[7];

    if (key == ECHO)
        return  
}