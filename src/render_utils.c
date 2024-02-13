/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:21:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/13 13:39:32 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	pixel_put_texture(t_general *gen, t_img *img, int x, int y)
{
	unsigned int	color;
	int			pixelx;
	int			pixely;
	
	pixelx = x % 64;
	pixely = y % 64;
	
	if (pixelx >= 0 && pixelx < img->width && pixely >= 0 && pixely < img->height)
		color = *(unsigned int *)(img->addr + ((int)pixely * img->line_length) + ((int)pixelx * img->bits_per_pixel / 8));
	else
		color = 0;
	my_mlx_pixel_put(gen->img, x, y, color);
}

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

float	ft_tan(float angle)
{
	float	s;
	float	c;

	s = sin(toRad(angle));
	c = cos(toRad(angle));
	if (fabs(c) > 0.0001)
		return (s / c);
	return (s);
}
