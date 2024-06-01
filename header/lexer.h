

#ifndef LEXER_H
# define LEXER_H

#define PIPE 1
#define GREAT 2
#define LESS 3
#define GREATGREAT 4
#define LESSLESS 5

#include "minishell.h"

//LEXER
t_lexer	*lexer(t_tools *tools);
t_lexer	*get_next_lex(char *str, t_tools *tools);
t_lexer	*set_lexer(char	*str, int tkn);
t_lexer	*add_lexer(t_lexer **lexer_lst, t_lexer *new_lex);
int		is_token(char c);
int		get_token(char *str);

//UTILS
void	print_lexer(t_lexer *lexer);
void	free_lexer(t_lexer **lex_lst);
int		is_space(char c);

//SYNTAX
int check_double_tk(t_tools *tools);
//ENVIRONMENT
t_env   *env_init(char **env);
t_env	*env_create(char *name, char *content);
t_env	*add_env(t_env **env_lst, t_env *new_env);
void    free_env(t_env **env_lst);
int     update_exit(t_env *env_lst);
void	print_env(t_env *env_lst);
//EXPANSOR
int     is_quote(char c);
t_lexer *expand(t_lexer *lexer_lst, t_env *env_lst);
char    *search_env(char *str, t_env *env_lst);
char	*find_env(char *name, t_env *env_lst);
char    *expand_env(char *env_str, t_env *env_lst, char quote);
//PATHS
char	*find_path(t_env *env_lst);
void    get_paths(t_tools *tools, t_env *env_lst);
void	free_matrix(char **matrix);
//QUOTES
void    check_quotes(t_lexer *lexer_lst);
char    *clean_quotes(char *str);

#endif