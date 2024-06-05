/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:48:42 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 13:48:42 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
// $ dentro de "" se expande
/*Returns malloc'd string of the word in the $variable*/
int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*get_env_name(char *env_str, char quote)
{
	int		i;
	char	*name;

	i = 1;
	if (!env_str[1])
		return ("");
	if (env_str[1] == quote || (is_quote(env_str[1]) && quote == 0))
		return (NULL);
	while (env_str[i] && !is_space(env_str[i]) \
	&& !is_quote(env_str[i]) && !is_token(env_str[i]) \
	&& env_str[i] != '$')
		i++;
	name = ft_malloc(i * sizeof(char));
	ft_strlcpy(name, env_str + 1, i);
	return (name);
}

int	get_env_name_len(char *env_str)
{
	int	i;

	i = 1;
	while (env_str[i] && !is_space(env_str[i]) \
	&& !is_quote(env_str[i]) && !is_token(env_str[i]) \
	&& env_str[i] != '$')
		i++;
	return (i);
}

/*Searches the variable inside the list*/
char	*find_env(char *name, t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i)
	{
		if (!ft_strncmp(name, env_i->name, ft_strlen(env_i->name)) \
		&& !ft_strncmp(name, env_i->name, ft_strlen(name)) \
		&& env_i->content)
			return (ft_strdup(env_i->content));
		env_i = env_i->next;
	}
	return (NULL);
}
