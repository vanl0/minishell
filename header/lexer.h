

#ifndef LEXER_H
# define LEXER_H

#define PIPE 1
#define GREAT 2
#define LESS 3
#define GREATGREAT 4
#define LESSLESS 5

typedef struct s_lexer
{
	char            *str;
	int             token;
	int				i;
	struct s_lexer  *next;
	struct s_lexer  *prev;
}   t_lexer;


//LEXER
t_lexer	*lexer(char *str);
t_lexer	*set_lexer(char	*str, int tkn);
t_lexer	*add_lexer(t_lexer **lexer_lst, t_lexer *new_lex);
t_lexer	*get_next(char	*str);
//UTILS
void	print_lexer(t_lexer *lexer);
void	free_lexer(t_lexer **lex_lst);

#endif