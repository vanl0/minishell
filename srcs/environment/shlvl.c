#include "minishell.h"

char *new_shlvl(char *str)
{
    int     shlvl;
    char    *new_shlvl;
    char    *shlvl_str;
    
    if (str)
    {
        shlvl = ft_atoi(str + 6) + 1;
        if (shlvl < 0)
            shlvl = 0;
        if (shlvl > 1000)
        {
            ft_putstr_fd("warning: shell level (", STDERR_FILENO);
            ft_putnbr_fd(shlvl, STDERR_FILENO);
            ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
            shlvl = 1;
        }
        shlvl_str = ft_itoa(shlvl);
    }
    else
        shlvl_str = ft_strdup("1");
    new_shlvl = ft_malloc(ft_strlen("SHLVL=") * sizeof(char) + sizeof(shlvl_str));
    ft_strlcpy(new_shlvl, "SHLVL=", ft_strlen("SHLVL=") + 1);
    ft_strlcat(new_shlvl, shlvl_str, ft_strlen("SHLVL=") * sizeof(char) + sizeof(shlvl_str));
    free(shlvl_str);
    return (new_shlvl);
}


char **increment_shlvl(char **env)
{
    int     env_size;
    char    **new_env;
    int     i;
    int     add;

    env_size = 0;
    i = 0;
    add = 1;
    while (env[env_size])
    {
        if (!ft_strncmp(env[env_size], "SHLVL=", 6))
            add = 0;
        env_size++;
    }
    new_env = malloc((env_size + 1 + add) * sizeof(char *));
    while (i < env_size)
    {
        if (!ft_strncmp(env[i], "SHLVL=", 6))
            new_env[i] = new_shlvl(env[i]);
        else
            new_env[i] = ft_strdup(env[i]);
        i++;
    }
    if (add)
        new_env[i++] = new_shlvl(NULL);
    new_env[i] = NULL;
    return (new_env);
}
