/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:09 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 12:43:10 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*remove_quote(char *str, int *start, int *end)
{
	char	*new_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_word = ft_malloc((ft_strlen(str) - 2 + 1) * sizeof(char));
	while (str[i])
	{
		if (i == *start)
			i++;
		if (i == *end)
			i++;
		if (str[i])
		{
			new_word[j] = str[i];
			j++;
			i++;
		}
	}
	new_word[j] = '\0';
	free(str);
	*end = *end - 1;
	*start = *end;
	return (new_word);
}

char	*clean_quotes(char *str)
{
	char	quote;
	int		i;
	int		start;

	i = 0;
	quote = 0;
	start = 0;
	if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
		return (str);
	while (str[i])
	{
		if (quote != 0 && str[i] == quote)
		{
			str = remove_quote(str, &start, &i);
			quote = 0;
		}
		else if (quote == 0 && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i];
			start = i++;
		}
		else
			i++;
	}
	return (str);
}

void	check_quotes(t_lexer *lexer_lst)
{
	t_lexer	*lexer_i;

	lexer_i = lexer_lst;
	while (lexer_i)
	{
		if (lexer_i->str)
			lexer_i->str = clean_quotes(lexer_i->str);
		lexer_i = lexer_i->next;
	}
}

// char	*clean_quotes(char *str)
// {
// 	char	quote;
// 	int		i;
// 	int		start;

// 	i = 0;
// 	quote = 0;
// 	start = 0;
// 	if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
// 		return (str);
// 	while (str[i])
// 	{
// 		if (quote != 0 && str[i] == quote)
// 		{
// 			str = remove_quote(str, start, &i);
// 			start = i;
// 			quote = 0;
// 		}
// 		else if (quote == 0 && (str[i] == '"' || str[i] == '\''))
// 		{
// 			quote = str[i];
// 			start = i;
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (str);
// }