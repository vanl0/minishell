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

void	update_wd(t_env *env_lst, char *arg)
{
	t_env	*env_i;
	char	*new_wd;

	if (arg[0] && arg[0] == '/')
		new_wd = ft_strdup(arg);
	env_i = env_lst;
	while (env_i)
	{
		if (!ft_strncmp("PWD=", env_i->name, ft_strlen(env_i->name)) && !ft_strncmp(name, env_i->name, ft_strlen(name)))
			return (ft_strdup(env_i->content));
		env_i = env_i->next;
	}
	return (NULL);
}

int	cd(t_simple_cmds *cmd)
{
	int		ret;
	char	*arg;
	char	*new_wd;

	arg = cmd->str[1];
	ret = chdir(cmd->str[1]);
	if (ret == EXIT_SUCCESS)
	{
		update_wd(cmd->tools->env_lst, arg);
	}
	return (ret);
}
