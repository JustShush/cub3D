/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:37:33 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:45:31 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Allocates memory for an array of 'n' elements of 'size' bytes each
//	The memory  is  set  to zero
//	Returns a pointer to the allocated memory

void	*ft_calloc(size_t n, size_t size)
{
	void	*buff;

	if ((n * size) > 2147483647)
		return (0);
	buff = (void *) malloc (size * n);
	if (!buff)
		return (NULL);
	ft_bzero(buff, n * size);
	return (buff);
}
