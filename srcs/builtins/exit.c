/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:28:19 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 14:28:19 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_nullify(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->line = NULL;
	tools->paths = NULL;
	tools->lexer_lst = NULL;
	tools->env_lst = NULL;
	tools->environ = NULL;
	g_signals.in_cmd = 0;
	g_signals.in_hdoc = 0;
	g_signals.stop_hdoc = 0;
}

int	free_tools(t_tools *tools)
{
	if (tools->simple_cmds)
		free_cmds(&tools->simple_cmds);
	if (tools->line)
		free(tools->line);
	if (tools->paths)
		free_matrix(tools->paths);
	if (tools->environ)
		free_matrix(tools->environ);
	if (tools->lexer_lst)
		free_lexer(&tools->lexer_lst);
	if (tools->env_lst)
		free_env(&tools->env_lst);
	exit_nullify(tools);
	return (EXIT_SUCCESS);
}

int	get_exit_code(char *str)
{
	int			i;
	long long	code;

	i = 0;
	if (str[0] == '\0')
		return (exit_error(str));
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ' ') || is_all_space(str))
			return (exit_error(str));
		i++;
	}
	code = atolonglong(str);
	return (code);
}

int	ft_exit(t_simple_cmds *cmd)
{
	int	exit_code;

	exit_code = cmd->tools->exit_code;
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->str[1] && ft_strncmp(cmd->str[1], "-9223372036854775808", 21))
	{
		exit_code = get_exit_code(cmd->str[1]);
		if (exit_code < 0)
			return (255);
	}
	free_tools(cmd->tools);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
