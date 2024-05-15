
#include "../header/minishell.h"


char    *remove_quote(char *str, int start, int end)
{
    char    *new_word;
    //char    quote;
    int     i;
    int     j;

    i = 0;
    j = 0;
    new_word = malloc((ft_strlen(str) - 2) * sizeof(char));
    while (str[i])
    {
        if (i == start)
            i++;
        if (i == end)
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
    return (new_word);
}
/*
"UNO"
UNO
UNO"DOS"TRES
UNODOSTRES
*/
char    *clean_quotes(char *str)
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
            str = remove_quote(str, start, i);
            quote = 0;
            i -= 2;
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

void    check_quotes(t_lexer *lexer_lst)
{
    t_lexer *lexer_i;

    lexer_i = lexer_lst;
    while (lexer_i)
    {
        if (lexer_i->str)
            lexer_i->str = clean_quotes(lexer_i->str);
        lexer_i = lexer_i->next;
    }

}