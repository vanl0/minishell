/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:31:13 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/04/30 16:31:14 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#define READLINE_LIBRARY
#define MAX_PATH 1024


#include <stdio.h>
#include "../readline-8.1/history.h"
#include "../readline-8.1/readline.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>



//PARSING
void    parse(char *line);

#endif