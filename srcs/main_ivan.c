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
    t_lexer *lexer_lst = NULL;
    char    *line;
    //t_tools *tools;

    env = NULL;
    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    /* while (1)
    {
        line = readline("minishell>");
        printf("\n%s\n", line);
        line = clean_quotes(line);
        printf("\n>%s<\n\n", line);
        free(line);
    } */
    line = readline("minishell>");
    lexer_lst = lexer(line);
    print_lexer(lexer_lst);
    printf("//////////////////////////////////////////////////////////////\n");
    check_quotes(lexer_lst);
    print_lexer(lexer_lst);
    free(line);
    free_lexer(&lexer_lst);
    return (0);
}
