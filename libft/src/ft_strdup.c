/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/13 13:43:53 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a pointer to a new string duplicated from the string 's'

char	*ft_strdup(const char *s)
{
	char	*buff;

	if (!s)
		return (NULL);
	buff = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s, ft_strlen(s) + 1);
	return (buff);
}
