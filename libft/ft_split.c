/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:52:57 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/26 18:00:17 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	words(char const *s, char c)
{
	size_t	words;
	int		isword;
	int		i;

	words = 0;
	isword = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && isword == 0)
		{
			isword = 1;
			words++;
		}
		else if (s[i] == c && isword == 1)
			isword = 0;
		i++;
	}
	return (words);
}

static size_t	wordlen(char const *s, char c, int i)
{
	size_t	wordlen;

	wordlen = 0;
	while (s[i] != c && s[i])
	{
		wordlen++;
		i++;
	}
	return (wordlen);
}

static char	**allfree(char **split)
{
	int	n;

	n = 0;
	while (split[n] != NULL)
	{
		free(split[n]);
		n++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = words(s, c);
	split = (char **)ft_malloc((n + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (j < n)
	{
		while (s[i] == c)
			i++;
		split[j] = ft_substr(s, i, wordlen(s, c, i));
		if (split[j] == NULL)
			return (allfree(split));
		i = i + wordlen(s, c, i);
		j++;
	}
	split[j] = NULL;
	return (split);
}
