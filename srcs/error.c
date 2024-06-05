/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:57:17 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 11:57:20 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_error(int flg, t_tools *tools)
{
	if (flg == QUOTE_ERROR)
		ft_putstr_fd("minishell: closing quote not found\n", STDERR_FILENO);
	if (flg == SYNTAX_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token\
		 `newline'\n", STDERR_FILENO);
	tools->exit_code = 2;
	clean_restart(tools);
	return (EXIT_FAILURE);
}
