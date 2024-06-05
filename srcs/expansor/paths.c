/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:48:42 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 13:48:42 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_matrix(char **strings)
{
	while (*strings)
		printf("%s\n", *strings++);
}

void	free_matrix(char **matrix)
{
	char	**t_matrix;

	t_matrix = matrix;
	while (*t_matrix)
		free(*t_matrix++);
	free(matrix);
}

char	*find_path(t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i && ft_strncmp(env_i->name, "PATH", 5) != 0)
	{
		env_i = env_i->next;
	}
	if (env_i == NULL)
	{
		return (NULL);
	}
	return (env_i->content);
}

void	get_paths(t_tools *tools, t_env *env_lst)
{
	tools->paths = ft_split(find_path(env_lst), ':');
}
