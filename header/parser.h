
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
	pid_t					child_pid;
	int						pipe_fd[2];
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

// PARSER
t_simple_cmds   *alloc_cmd(t_lexer *lex_lst);
t_simple_cmds   *parse(t_lexer *lexer_lst);
void			setup_cmd(t_simple_cmds *cmd, t_lexer **lex_lst);

// PARSER UTILS
int				count_args(t_lexer *lex_lst);
void			delete_first(t_lexer **lex_lst);
t_lexer			*make_redir(t_lexer **rd_node);
void			free_cmds(t_simple_cmds **cmds);

// UTILS
void    		print_cmds(t_simple_cmds *cmds);

//REDIRECTIONS
int 			check_redirections(t_simple_cmds *cmd);
int 			do_great(t_lexer *redirection);
int 			open_redir(t_lexer *redir);
//HEREDOC
int 			heredoc(t_simple_cmds *cmd);
char    		*get_hd_name(void);
int				do_heredoc(char *hd_file_name,  char *end);

#endif