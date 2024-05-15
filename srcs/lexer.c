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

/*
"A B"=A B
"A""B"=AB
"A" "B"=A B
A B=A B

'"'="
"'"='
'""'=""
'"'"'"="'
*/

void    *quote_err(void)
{
    printf("syntax error: open quotes\n");
    exit(0);
    return (NULL);
}

int quote_len(char *str)
{
    int     len;
    char    quote;

    len = 1;
    quote = *str;
    while (str[len] && str[len] != quote)
    {
        len++;
    }
    return (len + 1);
}
t_lexer *quote_lexer(char *str)
{
    int     i;
    char    *word;
    char    quote;

    i = 1;
    quote = *str;
    while (str[i])
    {
        if (str[i] == quote)
        {
            word = malloc((i + 2) * sizeof(char));
            ft_strlcpy(word, str, i + 2);
            return (set_lexer(word, 0));
        }
        i++;
    }
    return (quote_err());
}

t_lexer *get_next_lex(char *str)
{
    int i;
    char    *word;

    i = 0;
    if (is_token(str[i]))
        return (set_lexer(NULL, get_token(&str[i])));
    while (str[i] && is_space(str[i]) == 0 && !is_token(str[i]))
    {
        if (str[i] == '"' || str[i] == '\'')
            return (quote_lexer(&str[i]));
        i++;
    }
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
    if (str[i] == '"' || str[i] == '\'')
        return (quote_len(&str[i]));
    while (str[i] && is_space(str[i]) == 0 && !is_token(str[i]))
    {
        i++;
    }
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
        while (is_space(str[i]))
            i++;
        if (str[i])
        {
            lexer_i = get_next_lex(&str[i]);
            add_lexer(&lexer_lst, lexer_i);
        }
        i += skip_i(&str[i]);
    }
    //print_lexer(lexer_lst);
    return (lexer_lst);
}
