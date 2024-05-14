
#include "../header/minishell.h"

/* Sets a string in the t_simple_cmds struct */
t_simple_cmds   *set_str(t_simple_cmds *cmd, t_lexer *lex_lst);

/* Allocates memory for a t_simple_cmds struct.
It also sets all (lex_lst->(char **)str) arguments. */
t_simple_cmds   *create_cmd(t_lexer *lex_lst)
{
    t_lexer         *lexer_i;
    t_simple_cmds   *new_cmd;
    int             args_count;
    int             i;

    new_cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
    args_count = count_args(lex_lst);
    new_cmd->str = (char **)malloc((args_count + 1) * sizeof(char *));
    i = 0;
    lexer_i = lex_lst;
    while (lexer_i)
    {
        if (lexer_i->str)
            new_cmd->str[i] = lexer_i->str;
        ++i;
        lexer_i = lexer_i->next;
    }
    new_cmd->next = NULL;
    new_cmd->prev = NULL;
    return (new_cmd);
}

/* Returns a pointer to the next lexer that follows a PIPE */
t_lexer *get_next_cmd(t_lexer *lex_lst)
{
    t_lexer         *lexer_i;

    lexer_i = lex_lst;
    while (lexer_i)
    {
        if (lexer_i->token == PIPE)
            return (lexer_i->next);
        lexer_i = lexer_i->next;
    }
    return (NULL);
}

/* Adds a t_simple_cmds node to a t_simple_cmds list. If NULL, returns (new_cmd) */
t_simple_cmds   *add_cmd(t_simple_cmds **cmds_lst, t_simple_cmds *new_cmd)
{
    if (!cmds_lst)
        return (new_cmd);
    new_cmd->prev = *cmds_lst;
    (*cmds_lst)->next = new_cmd;
}

/* Takes a t_lexer list and loops through all its elements until it finds a PIPE.
All the elements before a PIPE are added as one node in a t_simple_cmds list. */
void    parse(t_lexer *lex_lst)
{
    t_lexer         *lexer_i;
	t_simple_cmds   *cmds_lst;

    cmds_lst = create_cmd(lex_lst);
	lexer_i = lex_lst;
	while (lexer_i && lexer_i->token != PIPE)
    {
        lexer_i = lexer_i->next;
    }
}
