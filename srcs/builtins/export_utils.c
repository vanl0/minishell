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
	char	**split;

	split = ft_split(str, '=');
	*name = split[0];
	if (split[1])
		*content = split[1];
	else
		*content = ft_strdup("");
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
