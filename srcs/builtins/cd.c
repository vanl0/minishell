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

/* checks if arg is a string consisting of only a hyphen (-)*/
static int	is_hyphen(char *arg)
{
	if (arg && arg[0] && !ft_strncmp(arg, "-", ft_strlen(arg)))
		return (1);
	return (0);
}

static char	*init_wd(char *old_wd)
{
	if (old_wd)
		return (ft_strdup(old_wd));
	return (ft_strdup("/"));
}

/* loops through arg and progressively builds the new working directory,
looking at the paths separated by '/' */
static char	*get_new_wd(char *arg, char *old_wd)
{
	int		i;
	char	*new_wd;
	char	*to_add;

	i = arg[0] == '/';
	new_wd = init_wd(old_wd);
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
		i += ft_strlen(to_add);
		i += arg[i] == '/';
		free(to_add);
	}
	return (new_wd);
}

static void	update_wd(t_tools *tools, char *arg, char *old_wd)
{
	char	*new_wd;

	new_wd = NULL;
	if (arg && arg[0] == '/')
		new_wd = get_new_wd(arg, NULL);
	else if (ft_strncmp(".", arg, ft_strlen(arg)))
		new_wd = get_new_wd(arg, old_wd);
	if (new_wd && env_exists("PWD", tools->env_lst))
	{
		search_n_destroy("PWD", tools);
		add_env(&tools->env_lst, env_create("PWD", new_wd));///////////////MODIFICACION
		free(new_wd);////////////////
	}
	search_n_destroy("OLDPWD", tools);
	add_env(&tools->env_lst, env_create("OLDPWD", old_wd));/////////////////MODIFICACION
}

int	cd(t_simple_cmds *cmd)
{
	char	*arg;
	char	cwd[PATH_MAX];

	arg = cmd->str[1];
	if (!cmd->str[1])
		arg = find_env("HOME", cmd->tools->env_lst);
	if (!arg)
		return (env_not_set("HOME"));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (EXIT_FAILURE);
	}
	if (is_hyphen(cmd->str[1]))
	{
		arg = find_env("OLDPWD", cmd->tools->env_lst);
		if (!arg)
			return (env_not_set("HOME"));
		if (access(arg, F_OK) == 0)
			printf("%s\n", arg);
	}
	if (chdir(arg) == -1 && ft_strncmp(cmd->str[1], "", 1))
		return (cd_error(arg, errno));
	update_wd(cmd->tools, arg, cwd);/////////////////MODIFICACION
	return (EXIT_SUCCESS);
}
