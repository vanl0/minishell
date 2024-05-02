/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:33:47 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/02/05 12:34:29 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nextelem;

	if (lst)
	{
		while (*lst)
		{
			nextelem = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = nextelem;
		}
	}
}
