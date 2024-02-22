/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:21:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:58:46 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_general *gen, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= gen->win_x || y < 0 || y >= gen->win_y)
		return ;
	dst = gen->img->addr
		+ (y * gen->img->line_length + x * (gen->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	norm(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

float	to_rad(float d)
{
	return (d * PI / 180);
}

float	ft_tan(float angle)
{
	float	s;
	float	c;

	s = sin(to_rad(angle));
	c = cos(to_rad(angle));
	if (fabs(c) > 0.000000001)
		return (s / c);
	return (1);
}

//Checks if point is inside the screen
//Returns 1 if wall or invalid
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 && y / CUB < gen->map->y
		&& x / CUB < ft_strlen(gen->map->tilemap[y / CUB])
		&& gen->map->tilemap[y / CUB][x / CUB] != '1')
		return (0);
	return (1);
}
