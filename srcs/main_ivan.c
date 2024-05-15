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
    //t_lexer *lexer_lst = NULL;
    char    *line;
    t_tools *tools;

    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    tools = tools_init();
    line = readline("minishell>");
    tools->lexer_lst = lexer(line);
    tools->env_lst = env_init(env);
    print_lexer(tools->lexer_lst);
    printf("//////////////////////////////////////////////////////////////\n");
    check_quotes(tools->lexer_lst, tools->env_lst);
    print_lexer(tools->lexer_lst);
    free(line);
    free_lexer(&(tools->lexer_lst));
    free_env(&tools->env_lst);
    return (0);
}
