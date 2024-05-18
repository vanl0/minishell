#include "minishell.h"

void	print_lines(int i, char **str, int fd)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
        i++;
		if (str[i])
			ft_putchar_fd(' ', fd);
	}
}

int	echo(t_simple_cmds *simple_cmd)
{
	int		i;
	int		j;
	int	    n_flg;

	i = 1;
    j = 0;
	n_flg = 0;
	while (simple_cmd->str[i] && simple_cmd->str[i][0] == '-'
		&& simple_cmd->str[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->str[i][j] == 'n')
			j++;
		if (simple_cmd->str[i][j] == '\0')
			n_flg = 1;
		else
			break ;
		i++;
	}
	print_lines(i, simple_cmd->str, STDOUT_FILENO);
	if (n_flg == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}