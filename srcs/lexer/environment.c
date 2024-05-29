/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 environment.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/15 17:38:26 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/05/15 17:38:27 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../header/minishell.h"

t_env	*env_create(char *name, char *content)
{
	t_env	*new_env;

	new_env = ft_malloc(sizeof(t_env));
	new_env->name = name;
	new_env->content = content;
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
		if (!ft_strncmp(env_i->name, "?", 1))
			env_i = env_i->next;
		else
		{
			if (env_i->content)
				printf("%s=%s\n", env_i->name, env_i->content);
			env_i = env_i->next;
		}
	}
}

/*Returns linked list t_env with name and content taken from the main argument
Also creates $? as an env variable, initialized at 0*/
t_env	*env_init(char **env)
{
	int		i;
	char	**line;
	t_env	*env_lst;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD", 6))
		{
			printf("AAAASDAFFFAFSFS\n");
			i++;
		}
		else
		{
			line = ft_split(env[i], '=');
			add_env(&env_lst, env_create(line[0], line[1]));
			free(line);
			i++;
		}
	}
	add_env(&env_lst, env_create(ft_strdup("?"), ft_itoa(g_signals.exit_stat)));
	return (env_lst);
}

int	update_exit(t_env *env_lst)
{
	while (env_lst)
	{
		if (!ft_strncmp(env_lst->name, "?", 1))
		{
			free(env_lst->content);
			env_lst->content = ft_itoa(g_signals.exit_stat);
			return (EXIT_SUCCESS);
		}
		env_lst = env_lst->next;
	}
	return (EXIT_FAILURE);
}