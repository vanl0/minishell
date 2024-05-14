/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:56:39 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/05/09 12:56:41 by ilorenzo         ###   ########.fr       */
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

int is_token(char c)
{
    if (c == '|')
        return (1);
    if (c == '>')
        return (1);
    if (c == '<')
        return (1);
    return (0);
}

int get_token(char *str)
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

t_lexer    *get_next_lex(char *str)
{
    int i;
    char    *word;

    i = 0;
    if (is_token(str[i]))
        return (set_lexer(NULL, get_token(&str[i])));
    while (str[i] && str[i] != ' ' && !is_token(str[i]))
        i++;
    word = malloc((i + 1) * sizeof(char));
    ft_strlcpy(word, str, i + 1);
    return (set_lexer(word, 0));
}

int skip_i(char *str)
{
    int i;

    i = 0;
    if (is_token(str[0]))
    {
        if (get_token(&str[0]) > 3)
            return (2);
        return (1);
    }
    while (str[i] && str[i] != ' ' && !is_token(str[i]))
        i++;
    return (i);
}

t_lexer    *lexer(char *str)
{
    int i;
    t_lexer *lexer_lst;
    t_lexer *lexer_i;

    i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i])
        {
            lexer_i = get_next_lex(&str[i]);
            add_lexer(&lexer_lst, lexer_i);
        }
        i += skip_i(&str[i]);
    }
    print_lexer(lexer_lst);
    return (lexer_lst);
}
