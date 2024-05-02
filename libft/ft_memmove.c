/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:53:12 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/21 11:01:30 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*cdest;
	char	*csrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	cdest = (char *)dest;
	csrc = (char *)src;
	if (csrc < cdest)
	{
		while (len-- > 0)
			cdest[len] = csrc[len];
	}
	else
	{
		while (i < len)
		{
			cdest[i] = csrc[i];
			i++;
		}
	}
	return (dest);
}
