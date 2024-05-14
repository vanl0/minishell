#include "../header/minishell.h"

t_env   *env_create(char *name, char *content)
{
    t_env   *new_env;

    new_env = malloc(sizeof(t_env));
    new_env->name = name;
    new_env->content = content;
    new_env->next = NULL;
    return(new_env);
}

t_env   *add_env(t_env **env_lst, t_env *new_env)
{
    t_env   *env_i;

    env_i = *env_lst;
    if (!(*env_lst))
    {
        *env_lst = new_env;
        return (new_env);
    }
    while (env_i->next)
        env_i = env_i->next;
    env_i->next = new_env;
    return (new_env);
}

/*Frees linked list*/
void    free_env(t_env **env_lst)
{
    t_env   *env_i;
    t_env   *env_free;

    env_free = *env_lst;
    env_i = env_free->next;
    while (env_i)
    {
        free(env_free->name);
        free(env_free->content);
        free(env_free);
        env_free = env_i;
        env_i = env_i->next;
    }
    free(env_free->name);
    free(env_free->content);
    free(env_free);
    *env_lst = NULL;
}

void    print_env(t_env *env_lst)
{
    t_env   *env_i;

    env_i = env_lst;
    while (env_i)
    {
        printf("name: %s, contnent: %s\n", env_i->name, env_i->content);
        env_i = env_i->next;
    }
}

/*Returns linked list t_env with name and content taken from the main argument*/
t_env   *env_init(char **env)
{
    int     i;
    char    **line;
    t_env   *env_lst;

    i = 0;
    env_lst = NULL;
    while (env[i])
    {
        line = ft_split(env[i], '=');
        add_env(&env_lst, env_create(line[0], line[1]));
        free(line);
        i++;
    }
    //print_env(env_lst);
    //free_env(&env_lst);
    return (env_lst);
}

