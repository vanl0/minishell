/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:52:32 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 13:52:32 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_shlvl(char *shlvl_str)
{
	char	*new_shlvl;

	new_shlvl = ft_malloc(ft_strlen("SHLVL=") \
	* sizeof(char) + sizeof(shlvl_str));
	ft_strlcpy(new_shlvl, "SHLVL=", ft_strlen("SHLVL=") + 1);
	ft_strlcat(new_shlvl, shlvl_str, ft_strlen("SHLVL=") \
	* sizeof(char) + sizeof(shlvl_str));
	return (new_shlvl);
}

char	*new_shlvl(char *str)
{
	int		shlvl;
	char	*new_shlvl;
	char	*shlvl_str;

	if (str)
	{
		shlvl = ft_atoi(str + 6) + 1;
		if (shlvl < 0)
			shlvl = 0;
		if (shlvl > 1000)
		{
			ft_putstr_fd("warning: shell level (", STDERR_FILENO);
			ft_putnbr_fd(shlvl, STDERR_FILENO);
			ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
			shlvl = 1;
		}
		shlvl_str = ft_itoa(shlvl);
	}
	else
		shlvl_str = ft_strdup("1");
	new_shlvl = create_shlvl(shlvl_str);
	free(shlvl_str);
	return (new_shlvl);
}

void	cpy_env(char **env, char **new_env, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			new_env[i] = new_shlvl(env[i]);
		else
			new_env[i] = ft_strdup(env[i]);
		i++;
	}
}

char	**increment_shlvl(char **env)
{
	int		env_size;
	char	**new_env;
	int		add;

	env_size = 0;
	add = 1;
	while (env[env_size])
	{
		if (!ft_strncmp(env[env_size++], "SHLVL=", 6))
			add = 0;
	}
	new_env = malloc((env_size + 1 + add) * sizeof(char *));
	cpy_env(env, new_env, env_size);
	if (add)
		new_env[env_size] = new_shlvl(NULL);
	new_env[env_size + add] = NULL;
	return (new_env);
}
