#include "minishell.h"
#include <sys/wait.h>
/*
this is basically ft_strjoin with a '/' added between the 2 strings */
char	*make_path(char *dir, char *command)
{
	char	*path;
	int		n;
	int		i;
	int		j;

	if (!dir || !command)
		return (NULL);
	n = ft_strlen(dir) + ft_strlen(command) + 2;
	path = malloc(n * sizeof(char));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (dir[++i])
		path[i] = dir[i];
    path[i++] = '/';
    j = -1;
	while (command[++j])
		path[i++] = command[j];
	path[i] = '\0';
	return (path);
}

char    *find_executable(t_simple_cmds *cmd, t_tools *tools)
{
    int     i;
    char    *command;
    char    *full_path;

    command = cmd->str[0];
    if (access(command, F_OK) == 0)
        return (command);
    i = -1;
    while (tools->paths[++i])
    {
        full_path = make_path(tools->paths[i], command);
        // handle malloc error
        if (access(full_path, F_OK) == 0)
            return (full_path);
        free(full_path);
    }
    return (NULL);
}

void    execute_cmd(t_simple_cmds *cmd, t_tools *tools)
{
    char    *path;
    /*
    pid_t   child_pid;
    int     status;
    */
    path = find_executable(cmd, tools);
    printf("path to command: %s\n", path);
    if (cmd->redirections)
    {
        heredoc(cmd);
        check_redirections(cmd);
    }
    if (!path)
    {
        printf("%s: command not found\n", cmd->str[0]);
        // handle error
        return ;
    }
    execv(path, cmd->str);
    free(path);
    // handle error: if execv fails, it returns.
}

void    execute_all(t_simple_cmds *cmds, t_tools *tools)
{
    t_simple_cmds   *tmp;
    int             pipefd[2];
    int             in_fd;
    pid_t           child_pid;

    in_fd = STDIN_FILENO; // For the first command
    tmp = cmds;
    while (tmp)
    {
        if (tmp->next)
        {
            if (pipe(pipefd) == -1)
                return ; // handle pipe error
        }
        child_pid = fork();
        if (child_pid < 0)
            return ; // handle fork error
        else if (child_pid == 0)
        {
            handle_child(pipefd, in_fd, tmp);
            execute_cmd(tmp, tools);
        }
        else
        {
            handle_parent(pipefd, &in_fd, tmp);
            waitpid(child_pid, NULL, 0); // change to waitpid(child_pid, &status, 0) and if (WIFEXITED(status)
        }
        tmp = tmp->next;
    }
}