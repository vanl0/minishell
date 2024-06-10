/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:10:02 by pde-masc          #+#    #+#             */
/*   Updated: 2024/06/05 20:10:04 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_lower_loop(char *str)
{
	while (*str)
	{
		ft_tolower(*str);
		str++;
	}
}

static void	my_dup2(int fd, int fd2)
{
	dup2(fd, fd2);
	close(fd);
}

static int	has_output(t_simple_cmds *cmd)
{
	t_lexer	*redir_i;

	redir_i = cmd->redirections;
	while (redir_i)
	{
		if (redir_i->token == GREAT || redir_i->token == GREATGREAT)
			return (0);
		redir_i = redir_i->next;
	}
	return (1);
}

/* reminder: 
- pipefd[0] is the fd for the read end
- pipefd[1] is the fd for the write end */
void	handle_child(int in_fd, int out_fd, char *path, t_simple_cmds *cmd)
{
	if (cmd->tools->exit_code != EXIT_SUCCESS)
	{
		free(path);
		exit(free_tools(cmd->tools));
	}
	if (in_fd != INVALID_FD)
		my_dup2(in_fd, STDIN_FILENO);
	if (check_redirections(cmd))
	{
		free(path);
		cmd->tools->exit_code = EXIT_FAILURE;
		exit(free_tools(cmd->tools));
	}
	if (out_fd != INVALID_FD && has_output(cmd))
		my_dup2(out_fd, STDOUT_FILENO);
	if (cmd->builtin == NULL)
	{
		update_environ(cmd->tools);
		execve(path, cmd->str, cmd->tools->environ);
		perror("execve");
		exit(errno);
	}
	else
		exit(cmd->builtin(cmd));
}

void	handle_parent(int in_fd, int out_fd, t_simple_cmds *cmd)
{
	if (is_minshell(cmd->str[0]))
		signal(SIGQUIT, SIG_IGN);
	cmd->pipe_fd[0] = in_fd;
	cmd->pipe_fd[1] = out_fd;
}
