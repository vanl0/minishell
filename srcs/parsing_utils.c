#include "../header/minishell.h"

void    do_pwd(void)
{
    char    cwd[MAX_PATH];
    
    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        printf("Error getting current path\n");
}

/* Counts the number of args before a PIPE. */
int count_args(t_lexer *lex_lst)
{
    t_lexer         *lexer_i;
    int             i;

    i = 0;
    lexer_i = lex_lst;
    while (lexer_i && lexer_i->token != PIPE)
    {
        if (lexer_i->str)
            ++i;
        lexer_i = lexer_i->next;
    }
    return (i);
}

void	delete_first(t_lexer **lex_lst)
{
    t_lexer *old;

    old = (*lex_lst);
    *lex_lst = (*lex_lst)->next;
    if (old->str)
        free(old->str);
    free(old);
}
