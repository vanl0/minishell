

#ifndef LEXER_H
# define LEXER_H

#define PIPE 1
#define GREAT 2
#define LESS 3
#define GREATGREAT 4
#define LESSLESS 5

#include "minishell.h"

//LEXER
t_lexer	*lexer(char *str);
t_lexer	*get_next_lex(char *str);
t_lexer	*set_lexer(char	*str, int tkn);
t_lexer	*add_lexer(t_lexer **lexer_lst, t_lexer *new_lex);
int		is_token(char c);
int		get_token(char *str);

//UTILS
void	print_lexer(t_lexer *lexer);
void	free_lexer(t_lexer **lex_lst);
int		is_space(char c);

//ENVIRONMENT
t_env   *env_init(char **env);
void    free_env(t_env **env_lst);
//EXPANSOR
char    *expand_env(char *env_str, t_env *env_lst);
//PATHS
void    get_paths(t_tools *tools, t_env *env_lst);
//QUOTES
void    check_quotes(t_lexer *lexer_lst, t_env *env_lst);
char    *clean_quotes(char *str, t_env *env_lst);

#endif