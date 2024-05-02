/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:03:40 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/21 12:02:27 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			ret = (char *) &str[i];
		i++;
	}
	if (str[i] == (char)c)
		return ((char *) &str[i]);
	return (ret);
}
