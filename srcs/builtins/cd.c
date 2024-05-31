/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:22:46 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/28 19:22:47 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Trims the last part of the directory path by removing the last '/' and everything after it */
char	*trim_from_back(char *dir)
{
	int	i;

	if (!dir)
		return (NULL);
	i = ft_strlen(dir);
	while (i--)
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

/* loops through arg and progressively builds the new working directory,
looking at the paths separated by '/' */
char	*get_new_wd(char *arg, char *old_wd)
{
	int		i;
	char	*new_wd;
	char	*to_add;

	new_wd = NULL;
	i = 0;
	new_wd = ft_strdup(old_wd);
	while (arg[i])
	{
		to_add = get_next_path(arg + i);
		if (!to_add)
		{
			free(new_wd);
			return (NULL);
		}
		if (!ft_strncmp("..", to_add, ft_strlen(to_add)))
			new_wd = trim_from_back(new_wd);
		else
			new_wd = make_path(new_wd, to_add);
		i += ft_strlen(to_add) + 1;
		free(to_add);
	}
	return (new_wd);
}

void	update_wd(t_tools *tools, char *arg)
{
	char	*new_wd;
	char	*old_wd;

	old_wd = find_env("PWD", tools->env_lst);
	new_wd = NULL;
	if (arg && arg[0] && arg[0] == '/')
		new_wd = ft_strdup(arg);
	else if (ft_strncmp(".", arg, ft_strlen(arg)))
		new_wd = get_new_wd(arg, old_wd);
	if (new_wd)
	{
		search_n_destroy("PWD", tools);
		add_env(&tools->env_lst, env_create(ft_strdup("PWD"), new_wd));
	}
	search_n_destroy("OLDPWD", tools);
	add_env(&tools->env_lst, env_create(ft_strdup("OLDPWD"), old_wd));
}

int	cd(t_simple_cmds *cmd)
{
	char	*arg;

	arg = cmd->str[1];
	if (!cmd->str[1])
		arg = find_env("HOME", cmd->tools->env_lst);
	if (chdir(arg) == -1 && ft_strncmp(cmd->str[1], "", 1))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	update_wd(cmd->tools, arg);
	return (EXIT_SUCCESS);
}

