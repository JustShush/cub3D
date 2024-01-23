/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:21:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 15:39:32 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Returns 0 if s1's first non space chars are equal to s2
int	first_str(char *s1, char *s2)
{
	while (*s1 == ' ')
		s1++;
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}
