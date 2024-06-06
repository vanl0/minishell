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
	tools.pid = NULL;
	tools.simple_cmds = NULL;
	tools.exit_code = 0;
	g_signals.in_cmd = 0;
	g_signals.in_hdoc = 0;
	g_signals.stop_hdoc = 0;
	start_signals();
	return (tools);
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