/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:21:39 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:31:21 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a substring from the string 's'
//	The substring begins at index 'c' and is of maximum size 'n'

char	*ft_substr(char const *str, int c, int n)
{
	char	*sub;
	int		i;

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
