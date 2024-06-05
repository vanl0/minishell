/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:38:58 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 12:39:00 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*Mallocs and initializes lexer struct*/
t_lexer	*set_lexer(char	*str, int tkn)
{
	t_lexer		*new_lex;
	static int	i = 0;

	new_lex = ft_malloc(sizeof(t_lexer));
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

char	*token_print(int token)
{
	if (token > 0)
	{
		if (token == PIPE)
			return ("PIPE");
		if (token == GREAT)
			return ("GREAT");
		if (token == LESS)
			return ("LESS");
		if (token == GREATGREAT)
			return ("GREATGREAT");
		if (token == LESSLESS)
			return ("LESSLESS");
	}
	return ("");
}

void	free_lexer(t_lexer **lex_lst)
{
	t_lexer	*lexer_i;
	t_lexer	*lexer_free;

	if (!lex_lst || !(*lex_lst))
		return ;
	lexer_free = *lex_lst;
	lexer_i = lexer_free->next;
	while (lexer_i)
	{
		if (lexer_free->str)
			free(lexer_free->str);
		free(lexer_free);
		lexer_free = lexer_i;
		lexer_i = lexer_i->next;
	}
	if (lexer_free->str)
		free(lexer_free->str);
	free(lexer_free);
	*lex_lst = NULL;
}

void	print_lexer(t_lexer *lexer)
{
	t_lexer	*lexer_i;
	char	*token;

	lexer_i = lexer;
	while (lexer_i)
	{
		token = token_print(lexer_i->token);
		printf("lexer:\nstr: >%s<\ntoken: %s\n", lexer_i->str, token);
		printf("----------\n");
		lexer_i = lexer_i->next;
	}
}
