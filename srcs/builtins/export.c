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
        return (1);
    while (*name)
    {
        if (!ft_isdigit(*name) && !ft_isalnum(*name) && *name != '_')
            return (1);
        name++;
    }
    return (0);
}

int export_elem(char *str, t_env *env_lst)
{
    char    *name;
    char    *content;

    if (str[0] == '=')
    {
        printf("export: %s: bad variable name\n", str);
        return(1);
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
        return (1);
    }
    return (setenv(name, content, 1));
}

int export_cmd(t_lexer *lexer_lst, t_env *env_lst)
{
    while(lexer_lst)
    {
        if (export_elem(lexer_lst->str, env_lst) != 0)
            return (1);
        lexer_lst = lexer_lst->next;
    }
    return (0);
}