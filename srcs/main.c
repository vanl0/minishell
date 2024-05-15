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
#include "../header/minishell.h"

//parse(line);
int main(void)
{
    t_lexer *lexer_lst;
    char    *line;
    t_simple_cmds   *commands;

    line = readline("minishell>");
    add_history(line);
    lexer_lst = lexer(line);
    commands = parse(lexer_lst);
    free(line);
    //free_lexer(&lexer_lst);
    return (0);
}
