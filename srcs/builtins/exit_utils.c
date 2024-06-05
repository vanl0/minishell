/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:13:31 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 15:13:32 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_error(char *str)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	return (-1);
}

long long int	get_longlong(char *str)
{
	int				i;
	int				digit;
	long long int	result;

	i = 0;
	result = 0;
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (result > (LLONG_MAX - digit) / 10)
			return (exit_error(str));
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

int	get_module(long long int result, int sign)
{
	if (result < 0)
		return (EXIT_FAILURE);
	if (sign == -1)
		result = -result;
	if (result < 0 || result > 255)
		result = result % 256;
	if (result < 0)
		result += 256;
	return (result);
}

int	atolonglong(char *str)
{
	int				sign;
	long long int	result;
	int				i;

	i = 0;
	sign = 1;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = get_longlong(&str[i]);
	return (get_module(result, sign));
}
