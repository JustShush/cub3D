/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:37:30 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 13:29:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_floor(t_general *gen, int draw_start, int i)
{
	while (draw_start < gen->win_y)
		my_mlx_pixel_put(gen, i, draw_start++,
			get_color(gen->textures->f));
}

void	draw_ceiling(t_general *gen, int draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
		my_mlx_pixel_put(gen, i, j++, get_color(gen->textures->c));
}

unsigned int	get_pixel_color(t_img *img, float pixelx, float pixely)
{
	unsigned int	color;

	if (pixelx >= 0 && pixelx < img->width
		&& pixely >= 0 && pixely < img->height)
		color = *(unsigned int *)(img->addr + (int)((pixely * img->line_length)
					+ (pixelx * img->bits_per_pixel / 2)));
	else
		color = 0;
	return (color);
}

void	draw_walls(t_general *gen, int x, t_su su, int flag)
{
	float			pixely;
	float			pixelx;
	unsigned int	color;

	pixely = (su.draw_start
			- (gen->win_y / 2) + (su.line_h / 2)) * 64 / su.line_h;
	if (flag == 0)
	{
		pixelx = (int)((gen->ray->hx + gen->ray->hy)) % 16;
		if (sin(to_rad(gen->ray->an)) > 0.0001)
			color = get_pixel_color(gen->textures->no, pixelx, pixely);
		else if (sin(to_rad(gen->ray->an)) < -0.0001)
			color = get_pixel_color(gen->textures->so, pixelx, pixely);
	}
	if (flag == 1)
	{
		pixelx = (int)((gen->ray->vx + gen->ray->vy)) % 16;
		if (cos(to_rad(gen->ray->an)) > 0.0001)
			color = get_pixel_color(gen->textures->ea, pixelx, pixely);
		else if (cos(to_rad(gen->ray->an)) < -0.0001)
			color = get_pixel_color(gen->textures->we, pixelx, pixely);
	}
	my_mlx_pixel_put(gen, x, su.draw_start, color);
}

void	draw(t_general *gen, float wall_dist, int i, int flag)
{
	t_su	su;

	su.proj_plane_dis = (gen->win_x / 2) / ft_tan(gen->pov);
	su.line_h = ((CUB / wall_dist) * su.proj_plane_dis);
	su.draw_start = (gen->win_y / 2) - (su.line_h / 2);
	su.draw_end = (gen->win_y / 2) + (su.line_h / 2);
	if (wall_dist < 0 || su.draw_start > gen->win_y)
		return ;
	else if (su.draw_start < 0)
	{
		su.draw_end = gen->win_y;
		su.draw_start = 0;
	}
	draw_ceiling(gen, su.draw_start, i);
	while (su.draw_start < su.draw_end)
	{
		draw_walls(gen, i, su, flag);
		su.draw_start++;
	}
	draw_floor(gen, su.draw_start, i);
}
