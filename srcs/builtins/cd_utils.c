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

/* better version of getcwd. It looks for PWD in env before using getcwd. */
char	*my_getcwd(t_tools *tools)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (env_exists("PWD", tools->env_lst))
			return (find_env("PWD", tools->env_lst));
		perror("getcwd error");
		return (NULL);
	}
	return (ft_strdup(cwd));
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
