/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:52:32 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 13:52:32 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	*env_create(char *name, char *content)
{
	t_env	*new_env;

	new_env = ft_malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	if (content)
		new_env->content = ft_strdup(content);
	else
		new_env->content = NULL;
	new_env->next = NULL;
	return (new_env);
}

t_env	*add_env(t_env **env_lst, t_env *new_env)
{
	t_env	*env_i;

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
void	free_env(t_env **env_lst)
{
	t_env	*env_i;
	t_env	*env_free;

	env_free = *env_lst;
	env_i = env_free->next;
	while (env_i)
	{
		free(env_free->name);
		if (env_free->content)
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

void	print_env(t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i)
	{
		if (env_i->content && ft_strncmp(env_i->name, "?", 1))
			printf("%s=%s\n", env_i->name, env_i->content);
		env_i = env_i->next;
	}
}

/*Returns linked list t_env with name and content taken from the main argument
Also creates $? as an env variable, initialized at 0*/
t_env	*env_init(char **env)
{
	int		i;
	char	**line;
	t_env	*env_lst;
	int		first;

	i = 0;
	env_lst = NULL;
	first = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "?=", 2))
			first = 1;
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			i++;
		else
		{
			line = ft_split(env[i], '=');
			add_env(&env_lst, env_create(line[0], line[1]));
			free_matrix(line);
			i++;
		}
	}
	if (first == 0)
		add_env(&env_lst, env_create("?", "0"));
	return (env_lst);
}
