/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:15:17 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Checks if it was given a char value that fits in the ASCII character set

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
