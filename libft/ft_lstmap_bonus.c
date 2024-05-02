/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <ilorenzo@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:31:28 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/02/06 12:31:08 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	void	*new_cont;
	t_list	*begin;

	if (!lst || !f || !del)
		return (NULL);
	new_cont = f(lst->content);
	new_list = ft_lstnew(new_cont);
	if (!new_list)
		return (del(new_cont), NULL);
	begin = new_list;
	lst = lst->next;
	while (lst)
	{
		new_cont = f(lst->content);
		new_list->next = ft_lstnew(new_cont);
		if (!new_list->next)
			return (del(new_cont), ft_lstclear(&begin, (*del)), NULL);
		new_list = new_list->next;
		lst = lst->next;
	}
	return (begin);
}
