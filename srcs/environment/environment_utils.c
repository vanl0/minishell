/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 environment_utils.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/06/02 18:07:41 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/06/02 18:07:41 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

char	*env_to_str(t_env *env)
{
	char	*str;
	int		len;

	len = ft_strlen(env->name) + 1;
	if (env->content)
		len += ft_strlen(env->content);
	str = ft_malloc((len + 1) * sizeof(char));
	ft_strlcpy(str, env->name, ft_strlen(env->name) + 1);
	ft_strlcat(str, "=", ft_strlen(env->name) + 2);
	if (env->content)
		ft_strlcat(str, env->content, len + 1);
	return (str);
}

int	env_len(t_env *env_lst)
{
	int		len;
	t_env	*env_i;

	len = 0;
	env_i = env_lst;
	while (env_i)
	{
		len++;
		env_i = env_i->next;
	}
	return (len);
}

void	update_environ(t_tools *tools)
{
	char	**new_environ;
	int		i;
	int		len;
	t_env	*env_i;

	i = 0;
	len = env_len(tools->env_lst);
	new_environ = ft_malloc((len + 1) * sizeof(char *));
	env_i = tools->env_lst;
	while (i < len)
	{
		new_environ[i] = env_to_str(env_i);
		i++;
		env_i = env_i->next;
	}
	free_matrix(tools->environ);
	tools->environ = new_environ;
	return ;
}
