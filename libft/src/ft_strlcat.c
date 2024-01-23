/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:52:01 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:47:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Appends the string 'src' to the end of 'dest'
//	It will append at most 'size' - strlen('dest') - 1 bytes

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	s;

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
