#include "minishell.h"

int pwd(t_simple_cmds *cmd)
{
    char    *pwd;

    pwd = find_env("PWD", cmd->tools->env_lst);
    if (!pwd)
        return (do_error(-1, cmd->tools));
    printf("%s\n", pwd);
    free(pwd);
    return (EXIT_SUCCESS);
}