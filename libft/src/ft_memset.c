/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:32:18 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:55 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Fills the first 'n' bytes of the memory area 's' with 'c'

void	*ft_memset(void *s, int c, int n)
{
	char	*buff;

	buff = (char *)s;
	while (n--)
		buff[n] = c;
	return (s);
}
