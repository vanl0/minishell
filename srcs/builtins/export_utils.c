/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:17:56 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 14:28:19 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	export_error(char *name, char *content)
{
	if (content)
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putstr_fd(content, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd("': bad variable name\n", STDERR_FILENO);
	}
	return ;
}

void	split_env(char *str, char **name, char **content)
{
	char	*eq_pos;
	int		name_len;
	int		cont_len;

	eq_pos = strchr(str, '=');
	if (!eq_pos)
	{
		*name = ft_strdup(str);
		*content = ft_strdup("");
		return ;
	}
	name_len = eq_pos - str;
	cont_len = ft_strlen(eq_pos + 1);
	*name = ft_malloc(name_len + 1);
	*content = ft_malloc(cont_len + 1);
	ft_strlcpy(*name, str, name_len + 1);
	ft_strlcpy(*content, eq_pos + 1, cont_len + 1);
}

int	check_name(char *name)
{
	if (ft_isdigit(name[0]) || ft_strchr(name, ' '))
		return (EXIT_FAILURE);
	while (*name)
	{
		if (!ft_isdigit(*name) && !ft_isalnum(*name) && *name != '_')
			return (EXIT_FAILURE);
		name++;
	}
	return (EXIT_SUCCESS);
}

// void	split_env2(char *str, char **name, char **content)
// {
// 	char	**split;

// 	split = ft_split(str, '=');
// 	*name = ft_strdup(split[0]);
// 	if (split[1])
// 		*content = ft_strdup(split[1]);
// 	else
// 		*content = ft_strdup("");
// 	free_matrix(split);
// }