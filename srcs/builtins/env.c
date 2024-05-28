#include "minishell.h"

int env(t_simple_cmds *cmd)
{
    print_env(cmd->tools->env_lst);
    return (EXIT_SUCCESS);
}