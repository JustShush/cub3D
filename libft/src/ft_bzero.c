/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:20:39 by mortins-          #+#    #+#             */
/*   Updated: 2024/01/31 15:27:49 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Erases the data in the first 'n' bytes of the memory starting at the
//	location pointed to by 's'

void	ft_bzero(void *s, int n)
{
	char	*buff;

	buff = (char *)s;
	while (n--)
		buff[n] = 0;
}
