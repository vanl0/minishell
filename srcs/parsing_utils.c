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

void    print_matrix(char **str)
{
    while (*str != NULL)
    {
        printf("[%s] ", *str);
        ++str;
    }
    printf("\n");
}

void    print_cmds(t_simple_cmds *cmds)
{
    t_simple_cmds *cmds_i;
    int i;
    
    cmds_i = cmds;
    i = 0;
    while (cmds_i)
    {
        printf("-----------------------------------\n");
        printf("New Command:\nCommand ID: %d\n", i++);
        printf(". . .\n");
        printf("Arguments\n");
        print_matrix(cmds_i->str);
        printf(". . .\n");
        if (cmds_i->redirections)
        {
            printf("Redirections Lexer List:\n");
            print_lexer(cmds_i->redirections);
        }
        else
            printf("No Redirections.\n");
        cmds_i = cmds_i->next;
        printf("-----------------------------------\n");
    }
}