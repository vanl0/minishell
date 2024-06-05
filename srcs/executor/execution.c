/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execution.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: pde-masc <pde-masc@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/24 17:13:03 by pde-masc		   #+#	  #+#			  */
/*	 Updated: 2024/05/24 17:13:51 by pde-masc		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int is_directory(char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
        return (0);
    return S_ISDIR(path_stat.st_mode);
}

void	to_lower_loop(char *str)
{
	while (*str)
	{
		ft_tolower(*str);
		str++;
	}
}

/* Allocates memory and returns the path to the command executable.
If the command is a builtin, it returns the duplicated command.
If the command is not found, it returns NULL.
*/
char	*find_executable(t_simple_cmds *cmd, char **paths)
{
	int		i;
	char	*command;
	char	*full_path;

	if (!paths)
		return (NULL);
	command = cmd->str[0];
	set_builtin(cmd);
	if (access(command, X_OK) == 0 || cmd->builtin != NULL)
	{
		full_path = ft_strdup(command);
		return (full_path);
	}
	i = -1;
	while (paths[++i])
	{
		full_path = make_path(paths[i], command);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

// returns exit code of executing cmd (which is the exit code of the child process)
int	execute_cmd(t_simple_cmds *cmd, int in_fd, int out_fd)
{
	char	*path;
	int		og_stdout;
	int		og_stdin;

	if (!cmd->str[0])
	{
		if (cmd->redirections)
		{
			og_stdout = dup(STDOUT_FILENO);
			og_stdin = dup(STDIN_FILENO);
			heredoc(cmd);
			if (check_redirections(cmd))
			{
				cmd->tools->exit_code = EXIT_FAILURE;
				clean_restart(cmd->tools);
				minishell(cmd->tools);
			}
		}
		if (cmd->redirections)
		{
			dup2(og_stdout, STDOUT_FILENO);
			dup2(og_stdin, STDIN_FILENO);
			close(og_stdout);
			close(og_stdin);
		}
		return (EXIT_SUCCESS);
	}
	cmd->tools->exit_code = EXIT_SUCCESS;
	path = find_executable(cmd, cmd->tools->paths);
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
	if (cmd->prev || cmd->next || builtin_key(path) == NOT_BUILTIN)
		execute_normal(in_fd, out_fd, path, cmd);
	else
	{
		if (cmd->redirections)
		{
			og_stdout = dup(STDOUT_FILENO);
			og_stdin = dup(STDIN_FILENO);
			heredoc(cmd);
			if (check_redirections(cmd))
			{
				cmd->tools->exit_code = EXIT_FAILURE;
				clean_restart(cmd->tools);
				minishell(cmd->tools);
			}
		}
		cmd->tools->exit_code = cmd->builtin(cmd);
		if (cmd->redirections)
		{
			dup2(og_stdout, STDOUT_FILENO);
			dup2(og_stdin, STDIN_FILENO);
			close(og_stdout);
			close(og_stdin);
		}
	}
	free(path);
	return (EXIT_SUCCESS);
}

void	execute_all(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	int				in_fd;
	int				pipe_fd[2];

	in_fd = INVALID_FD; // For the first command
	tmp = cmds;
	g_signals.in_cmd = 1;
	while (tmp)
	{
		if (tmp->next)
		{
			if (pipe(pipe_fd) == -1)
				return ; // handle pipe error
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
