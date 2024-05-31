/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:12:22 by pde-masc          #+#    #+#             */
/*   Updated: 2024/05/24 17:12:25 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char    *expand_home(void)
{
    char            *users;
    DIR             *dir;
    struct dirent   *entry;
    char            *full_path;

    users = "/Users";
    dir = opendir(users);
    if (dir == NULL)
    {
        perror("opendir");
        return (NULL);
    }
    entry = readdir(dir);
    while (entry)
    {
        if (entry->d_name[0] != '.' && ft_strncmp("Shared", entry->d_name, 6))
        {
            full_path = make_path(users, entry->d_name);
            if (access(full_path, R_OK | W_OK | X_OK) == 0)
                return (full_path);
            free(full_path);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return (NULL);
}

char    *return_expanded(char *arg)
{
    if (!arg)
        return (NULL);
    if (!ft_strncmp("~/", arg, 2))
        return (make_path(expand_home(), arg + 2));
    else if (!ft_strncmp("~", arg, ft_strlen(arg)))
        return (make_path(expand_home(), arg + 1));
    else
        return (ft_strdup(arg));
}

/*
this is basically ft_strjoin with a '/' added between the 2 strings */
char	*make_path(char *dir, char *to_add)
{
	char	*path;
	int		n;
	int		i;
	int		j;

	if (!dir || !to_add)
		return (NULL);
	n = ft_strlen(dir) + ft_strlen(to_add) + 2;
	path = malloc(n * sizeof(char));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (dir[++i])
		path[i] = dir[i];
    if (i - 1 >= 0 && path[i - 1] != '/')
        path[i++] = '/';
    j = -1;
	while (to_add[++j])
		path[i++] = to_add[j];
	path[i] = '\0';
    while (i > 0 && path[i - 1] == '/')
        path[--i] = '\0';
	return (path);
}

void    free_cmds(t_simple_cmds **cmds)
{
    t_simple_cmds   *cmd_tmp;
    int             i;
    int             status;

    while (*cmds)
    {
        cmd_tmp = *cmds;
        i = -1;
        while (cmd_tmp->str && cmd_tmp->str[++i])
            free(cmd_tmp->str[i]);
        free(cmd_tmp->str);
        free_lexer(&(cmd_tmp->redirections));
        if (cmd_tmp->hd_file_name)
            free(cmd_tmp->hd_file_name);
        if (cmd_tmp->child_pid > 0)
        {
            waitpid(cmd_tmp->child_pid, &status, 0);
            if (cmd_tmp->pipe_fd[0] != INVALID_FD)
                close(cmd_tmp->pipe_fd[0]);
            if (cmd_tmp->pipe_fd[1] != INVALID_FD)
                close(cmd_tmp->pipe_fd[1]);
            if (WIFEXITED(status))
		        g_signals.exit_stat = WEXITSTATUS(status);   
        }
        *cmds = (*cmds)->next;
        if (*cmds)
            (*cmds)->prev = NULL;
        free(cmd_tmp);
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
