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

char    *get_next_lex(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] && str[i] != ' ')
    {
        if (is_token(str[i]))
        {

        }
        
        i++;
    }
}

int skip_i(char *str)
{
    int i;

    i = 0;
    if (str[i])
    while (str[i] == )
}

char    *lexer(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (str[i])
        {
            
        }
        i += skip_i(&str[i]);
    }
    
}