/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:21:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/04 13:16:32 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	norm(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

float	toRad(float d)
{
	return (d * PI / 180);
}

//Returns 0 if s1's first non space chars are equal to s2
int	first_str(char *s1, char *s2)
{
	while (*s1 == ' ')
		s1++;
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (0);
	return (1);
}
