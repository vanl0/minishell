
#include "../header/minishell.h"
#include "../libft/libft.h"

void    do_pwd(void)
{
    char    cwd[MAX_PATH];
    
    if (getcwd(cwd, sizeof(cwd)))
        printf("%s\n", cwd);
    else
        printf("Error getting current path\n");
}

void    parse(char *line)
{
    if (ft_strncmp(line, "pwd", 4) == 0)
        do_pwd();
	else if (ft_strncmp(line, "cd ", 3) == 0)
		chdir(line + 3);
    else if (ft_strncmp(line, "exit", 4) == 0)
        return;
}
