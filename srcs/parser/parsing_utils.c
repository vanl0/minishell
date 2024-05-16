#include "../header/minishell.h"

void    print_mat(char **str)
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
        print_mat(cmds_i->str);
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

/* Deletes the first node in lex_lst */
void	delete_first(t_lexer **lex_lst)
{
    t_lexer *old;

    old = (*lex_lst);
    *lex_lst = (*lex_lst)->next;
    if (old->str)
        free(old->str);
    free(old);
}

/* Called whenever a redirection token is detected in the lexer.
Returns a lexer with token of rd_node, and string of rd_node->next. 
Also deletes rd_node from the list it was in. */
t_lexer  *make_redir(t_lexer **rd_node)
{
    char    *dest;
    t_lexer *rd;

    dest = ft_strdup((*rd_node)->next->str);
    if (!dest)
        return (NULL);
    rd = set_lexer(dest, 0);
    rd->token = (*rd_node)->token;
    delete_first(rd_node);
    return (rd);
}