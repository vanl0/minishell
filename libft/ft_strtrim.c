/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:35:27 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/29 17:46:34 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	checkbeg(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j] != '\0' && s1[i])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	return (i);
}

static size_t	checkend(char const *s1, char const *set, size_t len)
{
	size_t	j;

	j = 0;
	while (set[j] != '\0' && len >= 0)
	{
		if (s1[len] == set[j])
		{
			if (len == 0)
				return (0);
			len--;
			j = 0;
		}
		else
		{
			j++;
		}
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	a;
	size_t	b;
	size_t	i;

	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	a = checkbeg(s1, set);
	b = checkend(s1, set, (ft_strlen(s1) - 1));
	if (a > b)
		return (ft_strdup(""));
	i = 0;
	strtrim = (char *)malloc((b - a + 2) * sizeof(char));
	if (strtrim == NULL)
		return (NULL);
	while (i < (b - a + 1))
	{
		strtrim[i] = s1[a + i];
		i++;
	}
	strtrim[i] = '\0';
	return (strtrim);
}
