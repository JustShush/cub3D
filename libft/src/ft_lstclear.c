/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:15:48 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:24 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Deletes and frees the given node and all of its successors
//	using the function ’del’ and free

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	while (temp)
	{
		*lst = (*lst)-> next;
		ft_lstdelone(temp, del);
		temp = *lst;
	}
}
