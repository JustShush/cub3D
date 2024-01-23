/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:21:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:47:38 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a substring from the string 's'
//	The substring begins at index 'c' and is of maximum size 'n'

char	*ft_substr(char const *str, unsigned int c, size_t n)
{
	char	*sub;
	size_t	i;

	if (ft_strlen(str) <= c)
		n = 0;
	else if (n > (ft_strlen(str) - c))
		n = ft_strlen(str) - c;
	sub = (char *)malloc(sizeof(char) * (n + 1));
	if (!sub)
		return (0);
	i = 0;
	while (i < n)
		sub[i++] = str[c++];
	sub[i] = '\0';
	return (sub);
}
