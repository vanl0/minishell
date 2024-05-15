/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:38:50 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/05/15 17:38:51 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

//"1"2'3'4 4"1"2'3' '3'4"1"2 2'3'4"1" "1""1"2'4' '4''4'"1"2 "'" '"' "'$USER'" '"$USER"'
char    *remove_quote(char *str, int start, int *end, t_env *env_lst)
{
    char    *new_word;
    char    quote;
    int     i;
    int     j;

    i = 0;
    j = 0;
    quote = str[start];
    new_word = malloc((ft_strlen(str) - 2) * sizeof(char));
    while (str[i])
    {
        if (i == start)
            i++;
        if (i == *end)
            i++;
        if (str[i])
        {
            new_word[j] = str[i];
            j++;
            i++;
        }
        if (str[i] == '$' && quote == '\'')
        {
            //expand var and erase '' and realloc new_word and manage i value to change
        }
    }
    new_word[j] = '\0';
    free(str);
    *end = *end - 1;
    return (new_word);
}

char    *clean_quotes(char *str, t_env *env_lst)
{
    char    quote;
    int     i;
    int     start;

    i = 0;
    quote = 0;
    start = 0;
    if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
        return (str);
    while (str[i])
    {
        if (quote != 0 && str[i] == quote)//closed quote
        {
            str = remove_quote(str, start, &i, env_lst);
            quote = 0;
            //i -= 2;
            //i++;
            start = i;
        }
        else if (quote == 0 && (str[i] == '"' || str[i] == '\''))//new quote
        {
            quote = str[i];
            start = i;
            i++;
        }
        else
            i++;
    }
    return (str);
}

void    check_quotes(t_lexer *lexer_lst, t_env *env_lst)
{
    t_lexer *lexer_i;

    lexer_i = lexer_lst;
    while (lexer_i)
    {
        if (lexer_i->str)
            lexer_i->str = clean_quotes(lexer_i->str, env_lst);
        lexer_i = lexer_i->next;
    }
}
