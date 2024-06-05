/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:53:41 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 12:53:42 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_tk(int token)
{
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREATGREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESSLESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("`|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	return ;
}

int	is_great(int token)
{
	if (token == GREAT || token == GREATGREAT)
		return (1);
	return (0);
}
/*Checks
First is pipe
Double token
*/

int	check_double_tk(t_tools *tools)
{
	t_lexer	*lexer_i;

	lexer_i = tools->lexer_lst;
	if (lexer_i->token == PIPE)
	{
		ft_putstr_fd(SYNTAX_ERR_MSG, STDERR_FILENO);
		write_tk(lexer_i->token);
		return (do_error(-1, tools));
	}
	while (lexer_i->next)
	{
		if (lexer_i->token > 0 && lexer_i->next->token > 0 \
		&& !is_great(lexer_i->next->token) && lexer_i->next->next)
		{
			ft_putstr_fd(SYNTAX_ERR_MSG, STDERR_FILENO);
			write_tk(lexer_i->next->token);
			return (do_error(-1, tools));
		}
		lexer_i = lexer_i->next;
	}
	if (lexer_i->token > 0)
		return (do_error(1, tools));
	return (EXIT_SUCCESS);
}
