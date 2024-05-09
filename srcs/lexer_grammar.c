
#include "../header/minishell.h"

/*Errors to handle
    - token at the end
    - two or more tokens in a row?
    */

char    *tk_to_str(int token)
{
    if (token > 0)
	{
		if (token == PIPE)
			return ("'|'");
		if (token == GREAT)
			return ("'>'");
		if (token == LESS)
			return ("'<'");
		if (token == GREATGREAT)
			return ("'>>'");
		if (token == LESSLESS)
			return ("'<<'");
	}
	return ("<?>");
}

int check_lex_tokens(t_lexer *lexer_lst)
{
    t_lexer *lexer_i;

    lexer_i = lexer_lst;
    if (lexer_i->token > 0)
        return (printf("minishell: syntax error near unexpected token %s\n", tk_to_str(lexer_i->token)));
    while (lexer_i->next)
    {
        if ()
    }
}