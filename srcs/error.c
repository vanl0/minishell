/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 error.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/06/02 18:41:05 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/06/02 18:41:05 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*malloc_err(void)
{
	printf("malloc error\n");
	return (NULL);
}

int	do_error(int flg, t_tools *tools)
{
	if (flg == QUOTE_ERROR)
		ft_putstr_fd("minishell: closing quote not found\n", STDERR_FILENO);
	if (flg == SYNTAX_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	clean_restart(tools);
	return (EXIT_FAILURE);
}
