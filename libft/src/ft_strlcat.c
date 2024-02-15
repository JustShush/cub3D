/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:52:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:56 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Appends the string 'src' to the end of 'dest'
//	It will append at most 'size' - strlen('dest') - 1 bytes

unsigned int	ft_strlcat(char *dest, const char *src, int size)
{
	int	d;
	int	s;

	d = ft_strlen(dest);
	s = 0;
	if (size <= d)
		return (size + ft_strlen(src));
	while (src[s] && d + s < (size - 1))
	{
		dest[d + s] = src[s];
		s++;
	}
	dest[d + s] = '\0';
	return (ft_strlen(src) + d);
}
