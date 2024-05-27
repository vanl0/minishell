#include "minishell.h"

/* This function is called everytime tools is initialized. 
Every function takes (t_tools *, t_simple_cmds *) as arguments */
void    set_builtin_array(t_tools *tools)
{
    tools->builtins[ECHO] = echo;
    tools->builtins[CD] = cd;
    // set PWD
    // set EXPORT
    // set UNSET
    // set ENV
    // set EXIT
}

/* Returns the command's builtin key. -1 if not a builtin. */
int builtin_key(char *command)
{
    if (!ft_strncmp(command, "echo", 5))
        return (ECHO);
    if (!ft_strncmp(command, "cd", 3))
        return (CD);
    if (!ft_strncmp(command, "pwd", 4))
        return (PWD);
    if (!ft_strncmp(command, "export", 7))
        return (EXPORT);
    if (!ft_strncmp(command, "unset", 6))
        return (UNSET);
    if (!ft_strncmp(command, "env", 4))
        return (ENV);
    if (!ft_strncmp(command, "exit", 5))
        return (EXIT);
    return (NOT_BUILTIN);
}

/* This function is called before executing any command, in "find_executable".
If the command is a builtin, it sets the corresponding function in cmd->builtin.
Otherwise, it stays NULL.
*/
void    set_builtin(t_simple_cmds *cmd)
{
    int key;

    key = builtin_key(cmd->str[0]);
    if (key == NOT_BUILTIN)
        return ;
    cmd->builtin = cmd->tools->builtins[key];
}