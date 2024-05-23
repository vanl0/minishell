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
    {
        full_path = ft_strdup(command);
        // handle malloc error
        return (full_path);
    }
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

// returns exit code of executing cmd (which is the exit code of the child process)
int execute_cmd(t_simple_cmds *cmd, t_tools *tools, int in_fd, int out_fd)
{
    char    *path;
    //pid_t   child_pid;
    int     ret;

    ret = EXIT_SUCCESS;
    path = find_executable(cmd, tools);
    //printf("path to command: %s\n", path);
    // check redirections
    if (!path)
    {
        printf("%s: command not found\n", cmd->str[0]);
        // handle error
        return (EXIT_FAILURE); // idk
    }
    heredoc(cmd);
    cmd->child_pid = fork();
    if (cmd->child_pid < 0)
    {   // Error
        free(path);
        perror("fork");
        return (EXIT_FAILURE); // idk
    }
    if (cmd->child_pid == 0)
        handle_child(in_fd, out_fd, path, cmd);
    //else
        //ret = handle_parent(in_fd, out_fd, cmd->child_pid);
    free(path);
    return (ret);
}

void    execute_all(t_simple_cmds *cmds, t_tools *tools)
{
    t_simple_cmds   *tmp;
    int             pipefd[2];
    int             in_fd;

    in_fd = INVALID_FD; // For the first command
    tmp = cmds;
    while (tmp)
    {
        if (tmp->next)
        {
            if (pipe(pipefd) == -1)
                return ; // handle pipe error
            execute_cmd(tmp, tools, in_fd, pipefd[1]);
            close(pipefd[1]);
            if (in_fd != INVALID_FD)
                close(in_fd);
            in_fd = pipefd[0];
        }
        else
            execute_cmd(tmp, tools, in_fd, INVALID_FD);
        tmp = tmp->next;
    }
}
