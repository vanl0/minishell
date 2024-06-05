/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:28:19 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 14:28:19 by ilorenzo         ###   ########.fr       */
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

/* loops through arg and progressively builds the new working directory,
looking at the paths separated by '/' */
char	*get_new_wd(char *arg, char *old_wd)
{
	int		i;
	char	*new_wd;
	char	*to_add;

	new_wd = NULL;
	i = 0;
	if (old_wd)
		new_wd = ft_strdup(old_wd);
	else
		new_wd = ft_strdup("/");
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

void	update_wd(t_tools *tools, char *arg, char *old_wd)
{
	char	*new_wd;

	new_wd = NULL;
	if (arg && arg[0] && arg[0] == '/')
		new_wd = get_new_wd(arg, NULL);
	else if (ft_strncmp(".", arg, ft_strlen(arg)))
		new_wd = get_new_wd(arg, old_wd);
	if (new_wd && env_exists("PWD", tools->env_lst))
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
	char	cwd[PATH_MAX];

	arg = cmd->str[1];
	if (!cmd->str[1])
		arg = find_env("HOME", cmd->tools->env_lst);
	if (!arg)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd error");
		return (EXIT_FAILURE);
	}
	if (cmd->str[1] && cmd->str[1][0] && !ft_strncmp(cmd->str[1], "-", ft_strlen(cmd->str[1])))
	{
		arg = find_env("OLDPWD", cmd->tools->env_lst);
		if (!arg)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (access(arg, F_OK) == 0)
			printf("%s\n", arg);
	}
	if (chdir(arg) == -1 && ft_strncmp(cmd->str[1], "", 1))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	update_wd(cmd->tools, arg, ft_strdup(cwd));
	return (EXIT_SUCCESS);
}
