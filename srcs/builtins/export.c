/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:32:39 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/02 18:32:40 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
export UNO=1
export UNO - creates variable UNO but without value
export 1UNO - invalid name, only can start with _  or letter
export 1UNO DOS - won't create any variable, it stops as soon as it finds an error
export UNO 2DOS TRES- will display error and only create UNO. $? will save the error value.
*/

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

int	export_elem(char *str, t_tools *tools)
{
	char	*name;
	char	*content;

	if (str[0] == '=')
	{
		printf("export: %s: bad variable name\n", str);
		return (EXIT_FAILURE);
	}
	if (ft_strchr(str, '='))
		split_env(str, &name, &content);
	else
	{
		name = ft_strdup(str);
		content = NULL;
	}
	if (check_name(name))
	{
		export_error(name, content);
		tools->exit_code = 1;
		free(name);
		free(content);
		return (EXIT_FAILURE);
	}
	search_n_destroy(name, tools);
	add_env(&tools->env_lst, env_create(name, content));
	return (EXIT_SUCCESS);
}

void	print_exp(t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i)
	{
		if (!ft_strncmp(env_i->name, "?", 1))
			env_i = env_i->next;
		else
		{
			if (env_i->content)
				printf("declare -x %s=\"%s\"\n", env_i->name, env_i->content);
			else
				printf("declare -x %s\n", env_i->name);
			env_i = env_i->next;
		}
	}
}

/*
reads args and adds env variable to the t_env linked list,
NAME of the variable can only contain letters numbers(not the first) and underscore
a variable can be set with or without content, also can set multiple variables in one line
every declaration separated by space.  
errors:
- env name error
*/
int	export(t_simple_cmds *cmd)
{
	char	**args;
	int		i;

	args = cmd->str;
	i = 1;
	if (!args[i])
	{
		print_exp(cmd->tools->env_lst);
		return (EXIT_SUCCESS);
	}
	while (args[i])
	{
		export_elem(args[i], cmd->tools);
		i++;
	}
	return (cmd->tools->exit_code);
}
