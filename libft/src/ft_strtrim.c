/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:55 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/20 11:27:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a copy of 'str' with the characters specified in 'set' removed
//	from the beginning and the end of the string

char	*ft_strtrim(const char *s, const char *set)
{
	char	*buff;
	int		i;

	while (*s && ft_strchr(set, *s))
		s++;
	i = ft_strlen(s) - 1;
	while (i > 0 && ft_strchr(set, s[i]))
		i--;
	i++;
	buff = (char *)malloc(sizeof(char) * (i + 1));
	if (!buff)
		return (0);
	ft_strlcpy(buff, s, i + 1);
	return (buff);
}
