/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:30:33 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/04/30 16:30:35 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signals	g_signals;

t_tools	tools_init(char **env)
{
	t_tools	tools;

	tools.line = NULL;
	tools.environ = increment_shlvl(env);
	tools.env_lst = env_init(tools.environ);
	tools.paths = ft_split(find_path(tools.env_lst), ':');
	tools.lexer_lst = NULL;
	tools.pwd = NULL;
	tools.old_pwd = NULL;
	tools.pipes = 0;
	tools.pid = NULL;
	tools.simple_cmds = NULL;
	tools.exit_code = 0;
	g_signals.in_cmd = 0;
	g_signals.in_hdoc = 0;
	g_signals.stop_hdoc = 0;
	start_signals();
	return (tools);
}

int	clean_restart(t_tools *tools)
{
	if (tools->simple_cmds)
	{
		free_cmds(&tools->simple_cmds);
		tools->simple_cmds = NULL;
	}
	if (tools->line)
	{
		free(tools->line);
		tools->line = NULL;
	}
	if (tools->paths)
	{
		free_matrix(tools->paths);
		tools->paths = ft_split(find_path(tools->env_lst), ':');
	}
	if (tools->lexer_lst)
		free_lexer(&tools->lexer_lst);
	update_exit(tools);
	if (tools->pwd)
	{
		free(tools->pwd);
		tools->pwd = NULL;
	}
	if (tools->old_pwd)
	{
		free(tools->old_pwd);
		tools->pwd = NULL;
	}
	g_signals.in_cmd = 0;
	g_signals.in_hdoc = 0;
	g_signals.stop_hdoc = 0;
	start_signals();
	minishell(tools);
	return (EXIT_SUCCESS);
}

	/*if (tools->env_lst)
	{
	   free_env(&tools->env_lst);
	   tools->env_lst = NULL;
	}*/
	//tools->pipes = 0;
	//tools->pid = NULL;
	//g_signals.exit_stat = 0;

int	is_all_space(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

int	minishell(t_tools *tools)
{
	tools->line = readline("minishell>");
	add_history(tools->line);
	if (!tools->line)
	{
		printf("exit\n");
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

void	free_matrix_p(char **matrix)
{
	char	**t_matrix;

	t_matrix = matrix;
	while (*t_matrix)
	{
		printf("free: %s\n", *t_matrix);
		free(*t_matrix++);
	}
	free(matrix);
}

int	main(int argc, char **argv, char **env)
{
	t_tools	tools;

	tools = tools_init(env);
	if (argc != 1 || argv[1])
		exit(printf("This program does not accept arguments\n"));
	minishell(&tools);
	return (tools.exit_code);
}
	//printf("////////////////////////////////////////////\n");
	//update_environ(&tools);
	//for (int i = 0; tools.environ[i] != NULL; i++) {
	//    printf("%s\n", tools.environ[i]);
	//}
	//free_env(&tools.env_lst);
	//free_matrix_p(tools.environ);
	//free_matrix(tools.paths);