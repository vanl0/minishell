#include "minishell.h"

int	cd(t_simple_cmds *simple_cmd)
{
	printf("trying to execute %s\n", simple_cmd->str[0]);
	return (EXIT_SUCCESS);
}
