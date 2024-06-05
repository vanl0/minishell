/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ilorenzo <marvin@42.fr>		    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/06/05 11:54:18 by ilorenzo	       #+#    #+#	      */
/*   Updated: 2024/06/05 11:55:11 by ilorenzo         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "minishell.h"

int	nullify(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->line = NULL;
	tools->pwd = NULL;
	tools->old_pwd = NULL;
	g_signals.in_cmd = 0;
	g_signals.in_hdoc = 0;
	g_signals.stop_hdoc = 0;
	return (EXIT_SUCCESS);
}

int	clean_restart(t_tools *tools)
{
	if (tools->simple_cmds)
		free_cmds(&tools->simple_cmds);
	if (tools->line)
		free(tools->line);
	if (tools->paths)
	{
		free_matrix(tools->paths);
		tools->paths = ft_split(find_path(tools->env_lst), ':');
	}
	if (tools->lexer_lst)
		free_lexer(&tools->lexer_lst);
	if (tools->pwd)
		free(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	update_exit(tools);
	nullify(tools);
	start_signals();
	minishell(tools);
	return (EXIT_SUCCESS);
}

int	minishell(t_tools *tools)
{
	tools->line = readline("minishell>");
	add_history(tools->line);
	if (!tools->line)
	{
		printf("exit\n");
		free_tools(tools);
		exit(tools->exit_code);
	}
	if (tools->line[0] == '\0')
		clean_restart(tools);
	if (ft_strchr(tools->line, '$'))
		tools->line = search_env(tools->line, tools->env_lst);
	if (tools->line[0] == '\0' || is_all_space(tools->line))
		clean_restart(tools);
	lexer(tools);
	set_builtin_array(tools);
	tools->simple_cmds = parse(&tools->lexer_lst, tools);
	execute_all(tools->simple_cmds);
	clean_restart(tools);
	return (EXIT_FAILURE);
}
