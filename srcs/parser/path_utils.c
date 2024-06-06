/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:01 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/06 16:45:20 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_home(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*full_path;

	dir = opendir(USER_DIR);
	if (dir == NULL)
		return (opendir_err());
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && ft_strncmp("Shared", entry->d_name, 6))
		{
			full_path = make_path(USER_DIR, entry->d_name);
			if (access(full_path, R_OK | W_OK | X_OK) == 0)
			{
				closedir(dir);
				return (full_path);
			}
			free(full_path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*return_expanded2(char *arg)
{
	if (!arg)
		return (NULL);
	if (!ft_strncmp("~/", arg, 2))
		return (make_path(expand_home(), arg + 2));
	else if (arg[0] && !ft_strncmp("~", arg, ft_strlen(arg)))
		return (make_path(expand_home(), arg + 1));
	return (ft_strdup(arg));
}

char	*return_expanded(char *arg)
{
	char	*home;
	char	*path;

	if (!arg)
		return (NULL);
	home = expand_home();
	if (!ft_strncmp("~/", arg, 2))
	{
		path = make_path(home, arg + 2);
		free(home);
		return (path);
	}
	else if (arg[0] && !ft_strncmp("~", arg, ft_strlen(arg)))
	{
		path = make_path(home, arg + 1);
		free(home);
		return (path);
	}
	free(home);
	return (ft_strdup(arg));
}

/*
this is basically ft_strjoin with a '/' added between the 2 strings */
char	*make_path(char *dir, char *to_add)
{
	char	*path;
	int		n;
	int		i;
	int		j;

	if (!dir && to_add)
		return (ft_strdup(to_add));
	if (!dir || !to_add)
		return (NULL);
	n = ft_strlen(dir) + ft_strlen(to_add) + 2;
	path = malloc(n * sizeof(char));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (dir[++i])
		path[i] = dir[i];
	if (i - 1 >= 0 && path[i - 1] != '/')
		path[i++] = '/';
	j = -1;
	while (to_add[++j])
		path[i++] = to_add[j];
	path[i] = '\0';
	while (i > 0 && path[i - 1] == '/')
		path[--i] = '\0';
	return (path);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
