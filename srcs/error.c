
#include "../header/minishell.h"

void    *malloc_err(void)
{
    printf("malloc error\n");
    return (NULL);
}

int    do_error(int flg, t_tools *tools)
{
    if (flg == 0)
        ft_putstr_fd("minishell: closing quote not found\n", STDERR_FILENO);
    if (flg == 1)
       ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
    clean_tools(tools);
    minishell(tools);
    return (EXIT_FAILURE);
}