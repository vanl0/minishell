
#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_lexer
{
	char            *str;
	int             token;
	int				i;
	struct s_lexer  *next;
	struct s_lexer  *prev;
}   t_lexer;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	t_env					*env_lst;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer_lst;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	int                     heredoc;
	int                     reset;
}	t_tools;

typedef struct s_simple_cmds
{
	char                    **str;
	int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

// PARSER
t_simple_cmds   *parse(t_lexer *lex_lst);

// PARSER UTILS
int		count_args(t_lexer *lex_lst);
void	delete_first(t_lexer **lex_lst);

// UTILS
void    print_cmds(t_simple_cmds *cmds);

#endif