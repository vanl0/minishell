/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:31:33 by ilorenzo          #+#    #+#             */
/*   Updated: 2023/09/29 16:35:23 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getlen(int n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill(char *num, int n, size_t len, size_t neg)
{
	size_t	i;

	i = len + neg;
	num[i--] = '\0';
	if (neg == 1)
		num[0] = '-';
	while (n > 0 && i >= neg)
	{
		num[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	neg;
	size_t	len;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	len = getlen(n);
	num = (char *)malloc((neg + len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	fill(num, n, len, neg);
	return (num);
}
