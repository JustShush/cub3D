/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:29:30 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:52 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Scans the initial 'n' bytes of the memory area pointed to by 's' for the
//	first instance of 'c'

void	*ft_memchr(const void *s, int c, int n)
{
	int	i;
	char	*buff;

	i = 0;
	buff = (char *)s;
	if (!n)
		return (0);
	while (buff[i] != (char)c && i < n - 1)
		i++;
	if (buff[i] == (char)c)
		return (buff + i);
	return (0);
}
