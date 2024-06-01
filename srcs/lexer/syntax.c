#include "minishell.h"

void    write_tk(int token)
{
    if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREATGREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESSLESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
    return ;
}

int is_great(int token)
{
    if (token == GREAT || token == GREATGREAT)
        return (1);
    return (0);
}
/*Checks
First is token
Double token
*/
int check_double_tk(t_tools *tools)
{
    t_lexer *lexer_i;

    lexer_i = tools->lexer_lst;
    if (lexer_i->token == PIPE)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
        write_tk(lexer_i->token);
        g_signals.exit_stat = 2;
        do_error(-1, tools);
        return (EXIT_FAILURE);
    }
    while (lexer_i->next)
    {
        if (is_great(lexer_i->token) && lexer_i->next)
        {

        }
        else if (lexer_i->token > 0 && lexer_i->next->token > 0 && !is_great(lexer_i->next->token) && lexer_i->next->next)
        {
            ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
            write_tk(lexer_i->next->token);
            g_signals.exit_stat = 2;
            do_error(-1, tools);
            return (EXIT_FAILURE);
        }
        lexer_i = lexer_i->next;
    }
    if (lexer_i->token > 0)
    {
        g_signals.exit_stat = 2;
        do_error(1, tools);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}