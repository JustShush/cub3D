/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:09 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:26:24 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns the number of bytes in 's'

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
		i++;
	return (i);
}
