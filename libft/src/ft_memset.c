/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:32:18 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:48 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Fills the first 'n' bytes of the memory area 's' with 'c'

void	*ft_memset(void *s, int c, size_t n)
{
	char	*buff;

	buff = (char *)s;
	while (n--)
		buff[n] = c;
	return (s);
}
