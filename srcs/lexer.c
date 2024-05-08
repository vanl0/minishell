/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:25:23 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/05/07 16:25:24 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"



/*Mallocs and initializes lexer struct*/
t_lexer	*set_lexer(char	*str, int tkn)
{
	t_lexer		*new_lex;
	static	int	i = 0;

	new_lex = malloc(sizeof(t_lexer));
	new_lex->i = i;
	if (str)
	{
		new_lex->str = str;
		new_lex->token = 0;
	}
	else
	{
		new_lex->str = NULL;
		new_lex->token = tkn;
	}
	i++;
	return (new_lex);
}

/*Adds struct lexer to linked list*/
t_lexer	*add_lexer(t_lexer **lexer_lst, t_lexer *new_lex)
{
	t_lexer	*lexer_i;

	lexer_i = *lexer_lst;
	if (!(*lexer_lst))
	{
		new_lex->next = NULL;
		new_lex->prev = NULL;
		*lexer_lst = new_lex;
		return (new_lex);
	}
	while (lexer_i->next)
		lexer_i = lexer_i->next;
	lexer_i->next = new_lex;
	new_lex->prev = lexer_i;
	new_lex->next = NULL;
	return (new_lex);
}

/*Reads till space found, then returns lexer, token or string*/
t_lexer	*get_next(char	*str)
{
	static char		*start = NULL;
	int				i;
	char			*res;
	
	i = 0;
	if (!start)
		start = str;
	if (!start || !(*start))
		return (NULL);
	while (*start == ' ')
		start++;
	while (start[i] && start[i] != ' ')
		i++;
	if (i == 1)
	{
		if (*start == '|')
			return(start++, set_lexer(NULL, PIPE));
		if (*start == '>')
			return(start++, set_lexer(NULL, GREAT));
		if (*start == '<')
			return(start++, set_lexer(NULL, LESS));
	}
	if (i == 2)
	{
		if (ft_strncmp(start, ">>", 2) == 0)
			return(start += 2, set_lexer(NULL, GREATGREAT));
		if (ft_strncmp(start, "<<", 2) == 0)
			return(start += 2, set_lexer(NULL, LESSLESS));
	}
	res = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(res, start, i + 1);
	start = start + i;
	return (set_lexer(res, 0));
}

t_lexer	*lex(char *str)
{
	t_lexer	*lexer_lst;
	t_lexer	*new_lex;
	
	lexer_lst = NULL;
	new_lex = get_next(str);
	while (new_lex)
	{
		add_lexer(&lexer_lst, new_lex);
		new_lex = get_next(str);
	}
	print_lexer(lexer_lst);
	free_lexer(&lexer_lst);
	return (lexer_lst);
}

