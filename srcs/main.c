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

 t_signals   g_signals;
 
t_tools tools_init(char **env)
{
    t_tools tools;

    tools.line = NULL;
    tools.env_lst = env_init(env);
    tools.paths = ft_split(find_path(tools.env_lst), ':');
    tools.lexer_lst = NULL;
    tools.pwd = NULL;
    tools.old_pwd = NULL;
    tools.pipes = 0;
    tools.pid = NULL;
    tools.simple_cmds = NULL;
    g_signals.exit_stat = 0;
    g_signals.in_cmd = 0;
    g_signals.in_hdoc = 0;
    g_signals.stop_hdoc = 0;
    start_signals();
    return (tools);
}


int clean_tools(t_tools *tools)
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
   
    update_exit(tools->env_lst);
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
    /*if (tools->env_lst)
    {
       free_env(&tools->env_lst);
       tools->env_lst = NULL;
    }*/
    //tools->pipes = 0;
    //tools->pid = NULL;
    //g_signals.exit_stat = 0;
    g_signals.in_cmd = 0;
    g_signals.in_hdoc = 0;
    g_signals.stop_hdoc = 0;
    start_signals();
    return (EXIT_SUCCESS);
}

int minishell(t_tools *tools)
{
    tools->line = readline("minishell>");
    add_history(tools->line);
    if (!tools->line)
    {
        printf("exit\n");
        exit(g_signals.exit_stat);
    }
    if (tools->line[0] == '\0')
    {
        clean_tools(tools);
        minishell(tools);
    }
    lexer(tools);
    set_builtin_array(tools);
    tools->simple_cmds = parse(&tools->lexer_lst, tools);
    execute_all(tools->simple_cmds);
    clean_tools(tools);
    minishell(tools);
    return (EXIT_FAILURE);
}


int main(int argc, char **argv, char **env)
{
    t_tools         tools;

    tools = tools_init(env);
    if (argc != 1 || argv[1])
		exit(printf("This program does not accept arguments\n"));
    minishell(&tools);
    return (g_signals.exit_stat);
}
