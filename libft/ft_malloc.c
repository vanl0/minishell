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
    return (var);
}