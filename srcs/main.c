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


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *line = readline("Ingrese una línea: ");
    rl_replace_line("Línea reemplazada", 0);
    rl_redisplay();
    free(line);
    return 0;
}


/*
int main(void)
{
    char    *line;

    line = readline("minishell>");
    add_history(line);
    printf("%s\n", line);
    free(line);
    return (0);
}
*/