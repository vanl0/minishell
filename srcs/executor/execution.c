/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:58:06 by pde-masc          #+#    #+#             */
/*   Updated: 2024/06/05 19:49:54 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static void	execute_normal(int in_fd, int out_fd, char *path,
		t_simple_cmds *cmd)
{
	signal(SIGQUIT, handle_sigquit);
	cmd->child_pid = fork();
	if (cmd->child_pid < 0)
	{
		free(path);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cmd->child_pid == 0)
		handle_child(in_fd, out_fd, path, cmd);
	else
	{
		free(path);
		handle_parent(in_fd, out_fd, cmd);
	}
}

/* Allocates memory and returns the path to the command executable.
If the command is a builtin, it returns the duplicated command.
If the command is not found, it returns NULL.
*/
static char	*find_executable(t_simple_cmds *cmd, char **paths)
{
	int		i;
	char	*command;
	char	*full_path;

	command = cmd->str[0];
	set_builtin(cmd);
	if (!paths && !cmd->builtin)
		return (NULL);
	if (access(command, X_OK) == 0 || cmd->builtin != NULL)
	{
		full_path = ft_strdup(command);
		return (full_path);
	}
	i = -1;
	while (paths[++i])
	{
		full_path = make_path(ft_strdup(paths[i]), command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static void	check_path(t_simple_cmds *cmd, char *path)
{
	if (!path)
	{
		ft_putstr_fd(cmd->str[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		cmd->tools->exit_code = CMD_NOT_FOUND;
	}
	if (is_directory(path))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		cmd->tools->exit_code = IS_DIRECTORY;
	}
}

/* returns exit code of executing cmd.
(which is the exit code of the child process) */
static int	execute_cmd(t_simple_cmds *cmd, int in_fd, int out_fd)
{
	char	*path;

	if (!cmd->str[0])
	{
		handle_redirections(cmd);
		return (EXIT_SUCCESS);
	}
	path = find_executable(cmd, cmd->tools->paths);
	if (cmd->prev || cmd->next || !cmd->builtin)
	{
		cmd->tools->exit_code = EXIT_SUCCESS;
		check_path(cmd, path);
		execute_normal(in_fd, out_fd, path, cmd);
	}
	else
	{
		free(path);
		handle_redirections(cmd);
	}
	return (EXIT_SUCCESS);
}

/*Before executing anything sets the 
heredoc input file for each command*/
int	check_heredoc(t_simple_cmds *cmds)
{
	t_simple_cmds *cmd_i;

	cmd_i = cmds;
	while (cmd_i)
	{
		if (heredoc(cmd_i))
			return (HEREDOC_ERR);
		cmd_i = cmd_i->next;
	}
	return (EXIT_SUCCESS);
}

void	execute_all(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	int				in_fd;
	int				pipe_fd[2];

	in_fd = INVALID_FD;
	tmp = cmds;
	g_signals.in_cmd = 1;
	if (check_heredoc(cmds))
		return ;
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(pipe_fd) == -1)
				return ;
			execute_cmd(tmp, in_fd, pipe_fd[1]);
			close(pipe_fd[1]);
			if (in_fd != INVALID_FD)
				close(in_fd);
			in_fd = pipe_fd[0];
		}
		else
			execute_cmd(tmp, in_fd, INVALID_FD);
		tmp = tmp->next;
	}
}
