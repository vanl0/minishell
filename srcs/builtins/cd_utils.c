/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:37:51 by pde-masc          #+#    #+#             */
/*   Updated: 2024/06/05 18:56:58 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* looks if the env exists */
int	env_exists(char *name, t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i)
	{
		if (!ft_strncmp(name, env_i->name, ft_strlen(env_i->name)) \
		&& !ft_strncmp(name, env_i->name, ft_strlen(name)))
			return (1);
		env_i = env_i->next;
	}
	return (0);
}

/* Trims the last part of the directory path
by removing the last '/' and everything after it */
char	*trim_from_back(char *dir)
{
	int	i;

	if (!dir)
		return (NULL);
	i = ft_strlen(dir);
	while (i-- > 1)
	{
		if (dir[i] == '/')
		{
			dir[i] = '\0';
			return (dir);
		}
		dir[i] = '\0';
	}
	return (dir);
}

/* Extracts the next part of the path until the next '/' */
char	*get_next_path(char *arg)
{
	int		i;
	char	*path;

	i = 0;
	while (arg[i] && arg[i] != '/')
		++i;
	path = ft_malloc((i + 1) * sizeof(char));
	path[i] = '\0';
	while (--i >= 0)
		path[i] = arg[i];
	return (path);
}

int	env_not_set(char *env_name)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(env_name, STDERR_FILENO);
	ft_putstr_fd(" not set\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	cd_error(char *arg, int error)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(error), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
