
#include "../header/minishell.h"

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
void	print_lexer(t_lexer *lexer)
{
	t_lexer	*lexer_i;
	char 	*token;

	lexer_i = lexer;
	while (lexer_i)
	{
		token = token_print(lexer_i->token);	
		printf("lexer: %d\nstr: \"%s\"\ntoken: %s\nprev: %p | next: %p\n", lexer_i->i, lexer_i->str, token, lexer_i->prev, lexer_i->next);
		printf("-----------------------------------\n");
		lexer_i = lexer_i->next;
	}
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
		//printf("free %d\n", lexer_free->i);
		if (lexer_free->str)
			free(lexer_free->str);
		free(lexer_free);
		lexer_free = lexer_i;
		lexer_i = lexer_i->next;
	}
	//printf("free %d\n", lexer_free->i);
	if (lexer_free->str)
		free(lexer_free->str);
	free(lexer_free);
	*lex_lst = NULL;
}