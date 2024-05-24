/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 lexer.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/09 12:56:39 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/05/09 12:56:41 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

/*
"1"2'3'4 4"1"2'3' '3'4"1"2 2'3'4"1" "1""1"2'4' '4''4'"1"2 "'" '"' "'$USER'" '"$USER"'

if quote found
	curr_quote = 0 -> curr_quote = new one: CONTINUE
	curr_quote = new one: QUOTE CLOSED
	curr_quote != new one: CONTINUE
if quote closed
	next one is SPACE/NULL: RETURN string
	next one is NEW QUOTE: CONTINUE UNTIL NEW CLOSING QUOTE
	next one is NOT QUOTE/SPACE/END: CONTINUE UNTIL SPACE/NULL/NEW QUOTE
else
	ERROR
*/

void	*quote_err(void)
{
	printf("syntax error: open quotes\n");
	exit(0);
	return (NULL);
}

int	quote_len2(char *str)
{
	int		len;
	char	quote;

	len = 1;
	quote = *str;
	while (str[len] && str[len] != quote)
	{
		len++;
	}
	return (len + 1);
}

int	quote_len(char *str)
{
	int		i;
	char	quote;

	i = 1;
	quote = *str;
	while (str[i])
	{
		if (str[i] == quote)
		{
			if (is_space(str[i + 1]) || str[i + 1] == '\0')
			{
				return (i + 1);
			}
			if (str[i + 1] == '"' || str[i + 1] == '\'')
			{
				quote = str[i + 1];
				i++;
			}
			else
				quote = 0;
		}
		else
		{
			if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			{
				quote = str[i];
				i++;
			}
			if ((is_space(str[i + 1]) || str[i + 1] == '\0') && quote == 0)
			{
				return (i + 1);
			}
		}
		i++;
	}
	return (printf("syntax error: open quotes\n"));
}

t_lexer	*get_next_lex(char *str)
{
	int		i;
	char	*word;

	i = 0;
	if (is_token(str[i]))
		return (set_lexer(NULL, get_token(&str[i])));
	while (str[i] && is_space(str[i]) == 0 && !is_token(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += quote_len(&str[i]) - 1;
		}
		i++;
	}
	word = malloc((i + 1) * sizeof(char));
	ft_strlcpy(word, str, i + 1);
	return (set_lexer(word, 0));
}

int	skip_i(char *str)
{
	int	i;

	i = 0;
	if (is_token(str[0]))
	{
		if (get_token(&str[0]) > 3)
			return (2);
		return (1);
	}
	if (str[i] == '"' || str[i] == '\'')
		return (quote_len(&str[i]));
	while (str[i] && is_space(str[i]) == 0 && !is_token(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i += quote_len(&str[i]) - 1;
		}
		i++;
	}
	return (i);
}

/*this is not eficient at all but works for now*/
t_lexer	*lexer(char *str, t_tools tools)
{
	int		i;
	t_lexer	*lexer_lst;
	t_lexer	*lexer_i;

	i = 0;
	lexer_lst = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i])
		{
			lexer_i = get_next_lex(&str[i]);
			add_lexer(&lexer_lst, lexer_i);
		}
		i += skip_i(&str[i]);
	}
	check_quotes(lexer_lst);
	expand(lexer_lst, tools.env_lst);
	return (lexer_lst);
}
