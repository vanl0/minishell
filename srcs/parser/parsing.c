/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:12:34 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/24 17:12:35 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

/* Allocates memory for a t_simple_cmds struct and sets NULL values. */
t_simple_cmds   *alloc_cmd(t_lexer *lex_lst)
{
    
    t_simple_cmds   *new_cmd;
    int             args_count;

    new_cmd = (t_simple_cmds *)ft_malloc(sizeof(t_simple_cmds));
    args_count = count_args(lex_lst);
    new_cmd->str = (char **)ft_malloc((args_count + 1) * sizeof(char *));
    new_cmd->builtin = NULL;
    new_cmd->child_pid = NO_PID;
    new_cmd->str[args_count] = NULL;
    new_cmd->num_redirections = 0;
    new_cmd->redirections = NULL;
    new_cmd->hd_file_name = NULL;
    new_cmd->next = NULL;
    new_cmd->prev = NULL;
    return (new_cmd);
}

/* Sets up a t_simple_cmds struct (cmd):
- Checks first node, adds it as either an arg or a redirection in cmd.
- Deletes first node.
- Loop stops if nothing left, or if last node deleted was a pipe. */
void    setup_cmd(t_simple_cmds *cmd, t_lexer **lex_lst)
{
    t_lexer *new_redir;
    int     i;

    i = 0;
    while (*lex_lst)
    {
        if ((*lex_lst)->token == PIPE)
        {
            delete_first(lex_lst);
            break;
        }
        cmd->str[i] = NULL;
        if ((*lex_lst)->str)
            cmd->str[i++] = return_expanded((*lex_lst)->str);
        else
        {
            new_redir = make_redir(lex_lst);
            add_lexer(&(cmd->redirections), new_redir);
        }
        delete_first(lex_lst);
    }
    cmd->str[i] = NULL;
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
void   add_cmd(t_simple_cmds **cmds_lst, t_simple_cmds *new_cmd)
{
    t_simple_cmds   *cmds_i;

    if (!*cmds_lst)
    {
        *cmds_lst = new_cmd;
        return ;
    }
    cmds_i = *cmds_lst;
    while (cmds_i->next)
        cmds_i = cmds_i->next;
    cmds_i->next = new_cmd;
    new_cmd->prev = cmds_i;
}

/* Takes a t_lexer list and loops through all its elements until it finds a PIPE.
All the elements before a PIPE are added as one node in a t_simple_cmds list. */
t_simple_cmds   *parse(t_lexer **lex_lst_p, t_tools *tools)
{
	t_simple_cmds   *cmds_lst;
    t_simple_cmds   *current;
    t_lexer         *lex_lst;

    lex_lst = *lex_lst_p;
    cmds_lst = NULL;
    if (!lex_lst){
        return (NULL);
    }
	while (lex_lst)
    {
        current = alloc_cmd(lex_lst);
        setup_cmd(current, &lex_lst);
        current->tools = tools;
        add_cmd(&cmds_lst, current);
    }
    *lex_lst_p = NULL;
    return (cmds_lst);
}
