/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:02:26 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/10 14:02:27 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*var;

	var = malloc(size);
	if (!var)
	{
		ft_putstr_fd("malloc fail\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (var);
}
