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

long long int	atolonglong(const char *str)
{
	int				sign;
	long long int	result;
	int				digit;

	sign = 1;
	result = 0;
	digit = 0;
	while (isspace((unsigned char)*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (isdigit((unsigned char)*str))
	{
		digit = *str - '0';
		if (result > (LLONG_MAX - digit) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + digit;
		str++;
	}
	if (sign == 1)
		return (result);
	else
		return (-result);
}

void	exit_error(char *str)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
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
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ' ') || is_all_space(str))
		{
			exit_error(str);
			return (-1);
		}
		i++;
	}
	code = atolonglong(str);
	if (code < 0 || code > 255)
		code = code % 256;
	if (code < 0)
		code += 256;
	return (code);
}

int	ft_exit(t_simple_cmds *cmd)
{
	int	exit_code;

	exit_code = cmd->tools->exit_code;
	if (cmd->str[1] && cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (cmd->str[1])
	{
		exit_code = get_exit_code(cmd->str[1]);
		if (exit_code < 0)
			return (2);
	}
	free_tools(cmd->tools);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
