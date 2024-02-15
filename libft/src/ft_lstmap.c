/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:12:10 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/12 15:31:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Applies the function ’f’ on the data of each node
//	Creates a new list resulting of the applications of the function ’f’.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*head;
	t_list	*node;
	char	*data;

	if (!(lst && f && d))
		return (NULL);
	head = NULL;
	while (lst)
	{
		data = f(lst->data);
		node = ft_lstnew(data);
		if (!node)
		{
			d(data);
			ft_lstclear(&head, d);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst -> next;
	}
	ft_lstclear(&lst, d);
	return (head);
}
