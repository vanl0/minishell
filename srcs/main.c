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

t_tools *tools_init(void)
{
    t_tools *tools;

    tools = malloc(sizeof(t_tools));
    if (!tools)
        return (NULL);
    tools->args = NULL;
    tools->paths = NULL;
    tools->env_lst = NULL;
    tools->lexer_lst = NULL;
    tools->pwd = NULL;
    tools->old_pwd = NULL;
    tools->pipes = 0;
    tools->pid = NULL;
    return (tools);
}

//parse(line);

int main(int argc, char **argv, char **env)
{
    char            *line;
    t_tools         tools;
    t_simple_cmds   *commands;
    t_env           *env_lst;
    t_lexer         *lexer_lst;

    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    g_signals.exit_stat = 0;
    g_signals.in_cmd = 0;
    while (1)
    {
        g_signals.in_hdoc = 0;
        g_signals.stop_hdoc = 0;
        start_signals();
        line = readline("minishell>");
        if (!line)
        {
            printf("exit\n");
            exit(g_signals.exit_stat);
        }
        env_lst = NULL;
        env_lst = env_init(env);
        add_history(line);
        lexer_lst = lexer(line);
        check_quotes(lexer_lst);
        expand(lexer_lst, env_lst);
        commands = parse(lexer_lst);
        get_paths(&tools, env_lst);
        g_signals.in_cmd = 1;
        execute_all(commands, &tools);
        free_cmds(&commands);
        g_signals.in_cmd = 0;
        signal(SIGQUIT, SIG_IGN);
        //free_env(&env_lst);
        free(line);
    }
    //free_lexer(&lexer_lst);
    return (0);
}
