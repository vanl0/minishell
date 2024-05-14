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
int main(int argc, char **argv, char **env)
{
    t_env   *env_lst;

    if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    char    *line;
    line = readline("minishell>");
    add_history(line);
    lexer(line);
    free(line);
    free_env(&env_lst);
    return (0);
}
/*    env_lst = NULL;
    env_lst = env_init(env);
    expand_env("$PATHo", env_lst);*/