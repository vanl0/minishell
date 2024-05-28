#include "minishell.h"



int free_tools(t_tools *tools)
{
    if (tools->simple_cmds)
    {
        free_cmds(&tools->simple_cmds);
        tools->simple_cmds = NULL;
    }
    if (tools->line)
    {
        free(tools->line);
        tools->line = NULL;   
    }
    if (tools->paths)
        free_matrix(tools->paths);
    if (tools->lexer_lst)
        free_lexer(&tools->lexer_lst);
    if (tools->pwd)
    {
        free(tools->pwd);
        tools->pwd = NULL;
    }
    if (tools->old_pwd)
    {
        free(tools->old_pwd);
        tools->pwd = NULL;
    }
    if (tools->env_lst)
    {
       free_env(&tools->env_lst);
       tools->env_lst = NULL;
    }
    return (EXIT_SUCCESS);
}

int exit_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            ft_putstr_fd("sh: exit: ", STDERR_FILENO);
            ft_putstr_fd(str, STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int ft_exit(t_simple_cmds *cmd)
{
    int exit_code;

    exit_code = 0;
    if (cmd->str[1] && cmd->str[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    if (cmd->str[1])
    {
        if (exit_check(cmd->str[1]))
            return (255);
        else
        {
            exit_code = ft_atoi(cmd->str[1]);
            //return (EXIT_SUCCESS);
        }
    }
    free_tools(cmd->tools);
    exit(exit_code);
    return (EXIT_SUCCESS);
}