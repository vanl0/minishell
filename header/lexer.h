

#ifndef LEXER_H
# define LEXER_H

#define PIPE 1
#define GREAT 2
#define GREATGREAT 3
#define LESS 4
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
t_lexer	*lex(char *str);
t_lexer	*set_lexer(char	*str, int tkn);
t_lexer	*add_lexer(t_lexer **lexer_lst, t_lexer *new_lex);
t_lexer	*get_next(char	*str);

#endif