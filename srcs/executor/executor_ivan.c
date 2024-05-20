#include "minishell.h"

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
    pid_t   child_pid;
    int     status;

    path = find_executable(cmd, tools);
    if (cmd->redirections)
    {
        //should do something if this returns FAIL
        check_redirections(cmd->redirections);
    }
    if (!path)
    {
        printf("%s: command not found\n", cmd->str[0]);
        // handle error
        return ;
    }
    child_pid = fork();
    if (child_pid < 0) // error
    {
        free(path);
        return ;
    }
    else if (child_pid == 0)
        execv(path, cmd->str);
    else
    {
        waitpid(child_pid, &status, 0);
        //if (WIFEXITED(status))
        //   printf("Child process finished with exit code %d.\n", WEXITSTATUS(status));
    }
    free(path);
    // handle error: if execv fails, it returns.
}

void    execute_all(t_simple_cmds *cmds, t_tools *tools)
{
    t_simple_cmds *tmp;

    tmp = cmds;
    while (tmp)
    {
        execute_cmd(tmp, tools);
        tmp = tmp->next;
    }
}