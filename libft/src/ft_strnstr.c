/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:23:00 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:58 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Locates the first occurrence of the string 'lil' in the string 'big'
//	No more than 'n' characters are searched

char	*ft_strnstr(const char *big, const char *lil, int n)
{
	int	b;
	int	l;

	b = 0;
	if (!lil[0])
		return ((char *)big);
	if ((int)n < 0)
		n = ft_strlen(big);
	while (big[b] && b < n)
	{
		l = 0;
		while (big[b] != lil[l])
			b++;
		while (big[b + l] && big[b + l] == lil[l] && b + l < n)
		{
			if (lil[l + 1] == '\0')
				return ((char *)big + (b));
			l++;
		}
		b++;
	}
	return (0);
}
