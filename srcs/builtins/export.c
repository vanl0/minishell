#include "minishell.h"

/*
export UNO=1
export UNO - creates variable UNO but without value
export 1UNO - invalid name, only can start with _  or letter
export 1UNO DOS - won't create any variable, it stops as soon as it finds an error
export UNO 2DOS TRES- will display error and only create UNO. $? will save the error value.
*/

void    split_env(char *str, char **name, char **content)
{
    char    **split;

    split = ft_split(str, '=');
    *name = split[0];
    if (split[1])
        *content = split[1];
    else
        *content = ft_strdup("");
}

int check_name(char *name)
{
    if (ft_isdigit(name[0]) || ft_strchr(name, ' '))
        return (EXIT_FAILURE);
    while (*name)
    {
        if (!ft_isdigit(*name) && !ft_isalnum(*name) && *name != '_')
            return (EXIT_FAILURE);
        name++;
    }
    return (EXIT_SUCCESS);
}

int export_elem(char *str, t_env *env_lst)
{
    char    *name;
    char    *content;

    if (str[0] == '=')
    {
        printf("export: %s: bad variable name\n", str);
        return(EXIT_FAILURE);
    }
    if (ft_strchr(str, '='))
        split_env(str, &name, &content);
    else
    {
        name = str;
        content = NULL;
    }
    if (check_name(name))
    {
        printf("export: %s: bad variable name\n", name);
        free(name);
        free(content);
        return (EXIT_FAILURE);
    }
    add_env(&env_lst, env_create(name, content));
    return (EXIT_SUCCESS);
}

/*
reads args and adds env variable to the t_env linked list,
NAME of the variable can only contain letters numbers(not the first) and underscore
a variable can be set with or without content, also can set multiple variables in one line
every declaration separated by space.  
errors:
- env name error
*/
int export(t_simple_cmds *cmd)
{
    char    **args;
    int     i;

    args = cmd->str;
    i = 1;
    if (!args[i])
    {
        print_env(cmd->tools->env_lst);
        return (EXIT_SUCCESS);
    }
    while (args[i])
    {
        if (export_elem(args[i], cmd->tools->env_lst))
            return (EXIT_FAILURE);
        i++;
    }
    return (EXIT_SUCCESS);
}