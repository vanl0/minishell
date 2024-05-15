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
    tools->envp = NULL;
    tools->lexer_list = NULL;
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
    t_lexer         *lexer_lst;
    t_tools         tools;
    t_simple_cmds   *commands;
    t_env           *env_lst;

    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    line = readline("minishell>");
    //line = clean_quotes(line);
    lexer_lst = lexer(line);
    commands = parse(lexer_lst);
    env_lst = NULL;
    env_lst = env_init(env);
    //expand_env("$PATH", env_lst);
    get_paths(&tools, env_lst);
    execute_all(commands, &tools);
    free_env(&env_lst);
    //free(line);
    //free_lexer(&lexer_lst);
    return (0);
}
/*   */