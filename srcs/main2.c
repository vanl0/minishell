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

void    free_tools(t_tools **tools_p)
{
    t_tools *tools;

    tools = *tools_p;
    if (tools->paths)
        free_matrix(tools->paths);
    if (tools->env_lst)
        free_env(&tools->env_lst);
    //if (tools->lexer_lst)
   //     free_lexer(&tools->lexer_lst);
    free(tools);
    *tools_p = NULL;
    return ;
}

//parse(line);
int main(int argc, char **argv, char **env)
{
    char            *line;
    t_tools         *tools;
    t_simple_cmds   *commands;

    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    line = readline("minishell>");
    add_history(line);
    tools = tools_init();
    tools->env_lst = env_init(env);
    tools->lexer_lst = lexer(line);
    tools->lexer_lst = expand(tools->lexer_lst, tools->env_lst);
    check_quotes(tools->lexer_lst);
    commands = parse(tools->lexer_lst);
    //print_cmds(commands);
    get_paths(tools, tools->env_lst);
    execute_all(commands, tools);
    free_cmds(&commands);
    free_tools(&tools);
    free(line);

    //free_lexer(&lexer_lst);
    return (0);
}