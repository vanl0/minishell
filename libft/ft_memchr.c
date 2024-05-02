/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:52:11 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/17 16:38:17 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ucstr;
	size_t			i;

	ucstr = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		if (ucstr[i] == (unsigned char)c)
		{
			return ((void *)str + i);
		}
		i++;
	}
	return (NULL);
}
