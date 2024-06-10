/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:28:19 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 14:28:19 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_n_destroy(char *name, t_tools *tools)
{
	t_env	*env_i;
	t_env	*tmp_env;

	env_i = tools->env_lst;
	if (!strncmp(name, env_i->name, ft_strlen(env_i->name)))
	{
		tmp_env = env_i;
		tools->env_lst = env_i->next;
	}
	else
	{
		while (env_i->next && \
		ft_strncmp(name, env_i->next->name, ft_strlen(env_i->next->name) + 1))
			env_i = env_i->next;
		if (!env_i->next)
			return ;
		tmp_env = env_i->next;
		env_i->next = tmp_env->next;
	}
	if (tmp_env->name)
		free(tmp_env->name);
	if (tmp_env->content)
		free(tmp_env->content);
	free(tmp_env);
	return ;
}

//if name is wrong, it follows to the next one
int	unset_env(char *name, t_tools *tools)
{
	if (check_name(name))
	{
		ft_putstr_fd("unset: '", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	search_n_destroy(name, tools);
	return (EXIT_SUCCESS);
}

int	unset(t_simple_cmds *cmd)
{
	char	**str;
	int		i;

	str = cmd->str;
	i = 1;
	if (!str[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (str[i])
	{
		unset_env(str[i], cmd->tools);
		i++;
	}
	return (EXIT_SUCCESS);
}

// void	search_n_destroy2(char *name, t_tools *tools)
// {
// 	t_env	*env_i;
// 	t_env	*tmp_env;

// 	env_i = tools->env_lst;
// 	if (!strncmp(name, env_i->name, ft_strlen(env_i->name) + 1))
// 	{
// 		tools->env_lst = env_i->next;
// 		free(env_i->name);
// 		if (env_i->content)
// 			free(env_i->content);
// 		free(env_i);
// 		return ;
// 	}
// 	while (env_i->next)
// 	{
// 		if (!strncmp(name, env_i->next->name, ft_strlen(env_i->next->name) + 1))
// 		{
// 			tmp_env = env_i->next;
// 			env_i->next = tmp_env->next;
// 			free(tmp_env->name);
// 			if (tmp_env->content)
// 				free(tmp_env->content);
// 			free(tmp_env);
// 			return ;
// 		}
// 		env_i = env_i->next;
// 	}
// 	return ;
// }