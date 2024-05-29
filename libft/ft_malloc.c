#include "libft.h"

void *ft_malloc(size_t size)
{
    void    *var;

    var = malloc(size);
    if (!var)
    {
        ft_putstr_fd("malloc fail\n", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    ft_putstr_fd("malloc success\n", STDERR_FILENO);
    return (var);
}