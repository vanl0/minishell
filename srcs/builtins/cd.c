#include "minishell.h"

int	cd(t_simple_cmds *cmd)
{
	chdir(cmd->str[1]);
	return (EXIT_SUCCESS);
}
