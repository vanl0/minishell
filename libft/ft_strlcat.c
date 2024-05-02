/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:47:13 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/22 17:55:46 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	size_t			destsize;
	size_t			srcsize;

	i = 0;
	srcsize = ft_strlen(src);
	destsize = ft_strlen(dest);
	if (size <= destsize)
		return (srcsize + size);
	while (src[i] != '\0' && destsize + i < size - 1)
	{
		dest[destsize + i] = src[i];
		i ++;
	}
	dest[destsize + i] = '\0';
	return (srcsize + destsize);
}
