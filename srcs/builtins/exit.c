/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 exit.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/06/02 18:32:23 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/06/02 18:32:23 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	exit_error(char *str)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	return (-1);
}

int	atolonglong(char *str)
{
	int				sign;
	long long int	result;
	int				digit;
	int				i;

	i = 0;
	sign = 1;
	result = 0;
	digit = 0;
	while (isspace((unsigned char)str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (isdigit((unsigned char)str[i]))
	{
		digit = str[i] - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (exit_error(str));
		result = result * 10 + digit;
		i++;
	}
	if (sign == -1)
		result = -result;
	if (result < 0 || result > 255)
		result = result % 256;
	if (result < 0)
		result += 256;
	return ((int)result);
}

int	free_tools(t_tools *tools)
{
	if (tools->simple_cmds)
	{
		free_cmds(&tools->simple_cmds);
		tools->simple_cmds = NULL;
	}
	if (tools->line)
	{
		free(tools->line);
		tools->line = NULL;
	}
	if (tools->paths)
		free_matrix(tools->paths);
	if (tools->lexer_lst)
		free_lexer(&tools->lexer_lst);
	if (tools->pwd)
	{
		free(tools->pwd);
		tools->pwd = NULL;
	}
	if (tools->old_pwd)
	{
		free(tools->old_pwd);
		tools->pwd = NULL;
	}
	if (tools->env_lst)
	{
		free_env(&tools->env_lst);
		tools->env_lst = NULL;
	}
	return (EXIT_SUCCESS);
}

int	get_exit_code(char *str)
{
	int			i;
	long long	code;

	i = 0;
	if (str[0] == '\0')
		return (exit_error(str));
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ' ') || is_all_space(str))
			return (exit_error(str));
		i++;
	}
	code = atolonglong(str);
	return (code);
}

int	ft_exit(t_simple_cmds *cmd)
{
	int	exit_code;

	exit_code = cmd->tools->exit_code;
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmd->str[1] && ft_strncmp(cmd->str[1], "-9223372036854775808", 21))
	{
		exit_code = get_exit_code(cmd->str[1]);
		if (exit_code < 0)
			return (255);
	}
	free_tools(cmd->tools);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
