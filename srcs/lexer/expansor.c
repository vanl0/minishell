/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:38:16 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/05/15 17:38:17 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
// $ dentro de "" se expande
/*Returns malloc'd string of the word in the $variable*/
char    *get_env_name(char *env_str)
{
    int     i;
    char    *name;

    i = 1;
    if (!env_str[1])
        return (NULL);
    while(env_str[i] && !is_space(env_str[i]))
        i++;
    name = malloc(i * sizeof(char));
    ft_strlcpy(name, env_str + 1, i);
    return (name);
}

/*Searches the variable inside the list*/
char    *search_env(char *name, t_env *env_lst)
{
    t_env *env_i;

    env_i = env_lst;
    while (env_i)
    {
        if (ft_strncmp(name, env_i->name, ft_strlen(name)) == 0)
            return (env_i->content);
        env_i = env_i->next;
    }
    return (NULL);
}

/*Returns malloc'd string with the content of the variable, if not found returns ""*/
char    *expand_env(char *env_str, t_env *env_lst)
{
    char    *env_name;
    char    *content;   
    t_env   *env_i;

    env_name = get_env_name(env_str);
    env_i = env_lst;
    if (!env_name)
        return (NULL);
    content = search_env(env_name, env_lst);
    free(env_name);
    if (!content)
        return (NULL);
    printf("%s\n", content);
    //free(content);
    return (content);
}
