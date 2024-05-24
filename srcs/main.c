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

t_tools tools_init(char **env)
{
    t_tools tools;

    tools.args = NULL;
    tools.env_lst = env_init(env);
    tools.paths = ft_split(find_path(tools.env_lst), ':');
    tools.lexer_lst = NULL;
    tools.pwd = NULL;
    tools.old_pwd = NULL;
    tools.pipes = 0;
    tools.pid = NULL;
    g_signals.exit_stat = 0;
    g_signals.in_cmd = 0;
    g_signals.in_hdoc = 0;
    g_signals.stop_hdoc = 0;
    start_signals();
    return (tools);
}

int clean_tools(t_tools tools)
{
    if (tools.env_lst)
        free_env(&tools.env_lst);
    if (tools.paths)
        free_matrix(tools.paths);
    return (EXIT_SUCCESS);
}

int minishell(t_tools tools)
{
    char            *line;
    t_lexer         *lexer_lst;
    t_simple_cmds   *commands;

    for(int i = 0; i < 2; i++)
    {
        line = readline("minishell>");
        add_history(line);
        if (!line)
        {
            printf("exit\n");
            exit(g_signals.exit_stat);
        }
        lexer_lst = lexer(line, tools);
        commands = parse(lexer_lst);
        execute_all(commands, &tools);
        free_cmds(&commands);
        free(line);
        clean_tools(tools);
        tools = tools_init(env);
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    t_tools         tools;

    tools = tools_init(env);
    if (argc != 1 || argv[1])
		exit(printf("This program does not accept arguments\n"));
    minishell(tools);
    return (g_signals.exit_stat);
}

