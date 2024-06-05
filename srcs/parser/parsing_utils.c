/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:19:28 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 13:19:29 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_mat(char **str)
{
	while (*str != NULL)
	{
		printf("[%s] ", *str);
		++str;
	}
	printf("\n");
}

void	print_cmds(t_simple_cmds *cmds)
{
	t_simple_cmds	*cmds_i;
	int				i;

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

void	free_child(t_simple_cmds *cmd_tmp)
{
	int	status;

	waitpid(cmd_tmp->child_pid, &status, 0);
	if (cmd_tmp->pipe_fd[0] != INVALID_FD)
		close(cmd_tmp->pipe_fd[0]);
	if (cmd_tmp->pipe_fd[1] != INVALID_FD)
		close(cmd_tmp->pipe_fd[1]);
	if (WIFEXITED(status))
		cmd_tmp->tools->exit_code = WEXITSTATUS(status);
}

void	free_cmds(t_simple_cmds **cmds)
{
	t_simple_cmds	*cmd_tmp;

	while (*cmds)
	{
		cmd_tmp = *cmds;
		free_matrix(cmd_tmp->str);
		free_lexer(&(cmd_tmp->redirections));
		if (cmd_tmp->hd_file_name)
		{
			unlink(cmd_tmp->hd_file_name);
			free(cmd_tmp->hd_file_name);
		}
		if (cmd_tmp->child_pid > 0)
			free_child(cmd_tmp);
		*cmds = (*cmds)->next;
		if (*cmds)
			(*cmds)->prev = NULL;
		free(cmd_tmp);
	}
}

/* Counts the number of args before a PIPE. */
int	count_args(t_lexer *lex_lst)
{
	t_lexer		*lexer_i;
	int			i;

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
	t_lexer	*old;

	old = (*lex_lst);
	*lex_lst = (*lex_lst)->next;
	if (old->str)
		free(old->str);
	free(old);
}

/* Called whenever a redirection token is detected in the lexer.
Returns a lexer with token of rd_node, and string of rd_node->next. 
Also deletes rd_node from the list it was in. */
t_lexer	*make_redir(t_lexer **rd_node)
{
	char	*dest;
	t_lexer	*rd;

	dest = ft_strdup((*rd_node)->next->str);
	if (!dest)
		return (NULL);
	rd = set_lexer(dest, 0);
	rd->token = (*rd_node)->token;
	delete_first(rd_node);
	return (rd);
}
// void	free_cmds(t_simple_cmds **cmds)
// {
// 	t_simple_cmds	*cmd_tmp;
// 	int				i;
// 	int				status;

// 	while (*cmds)
// 	{
// 		cmd_tmp = *cmds;
// 		i = -1;
// 		while (cmd_tmp->str && cmd_tmp->str[++i])
// 			free(cmd_tmp->str[i]);
// 		free(cmd_tmp->str);
// 		free_lexer(&(cmd_tmp->redirections));
// 		if (cmd_tmp->hd_file_name)
// 		{
// 			unlink(cmd_tmp->hd_file_name);
// 			free(cmd_tmp->hd_file_name);
// 		}
// 		if (cmd_tmp->child_pid > 0)
// 		{
// 			waitpid(cmd_tmp->child_pid, &status, 0);
// 			if (cmd_tmp->pipe_fd[0] != INVALID_FD)
// 				close(cmd_tmp->pipe_fd[0]);
// 			if (cmd_tmp->pipe_fd[1] != INVALID_FD)
// 				close(cmd_tmp->pipe_fd[1]);
// 			if (WIFEXITED(status))
// 				cmd_tmp->tools->exit_code = WEXITSTATUS(status);
// 		}
// 		*cmds = (*cmds)->next;
// 		if (*cmds)
// 			(*cmds)->prev = NULL;
// 		free(cmd_tmp);
// 	}
// }