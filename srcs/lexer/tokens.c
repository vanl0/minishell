/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:29:55 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/02 20:29:56 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

/*Maybe here should add all isspace() definitions idk*/
int	is_space(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	get_token(char *str)
{
	if (str[1])
	{
		if (str[0] == '>' && str[1] == '>')
			return (GREATGREAT);
		if (str[0] == '<' && str[1] == '<')
			return (LESSLESS);
	}
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '>')
		return (GREAT);
	if (str[0] == '<')
		return (LESS);
	return (0);
}
