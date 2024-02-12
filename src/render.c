/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/12 12:17:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if point is inside the screen
//Returns 1 if wall or invalid
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 && y <= gen->win_y && x <= gen->win_x
		&& y / 64 < gen->map->y 
		&& x / 64 < ft_strlen(gen->map->tilemap[y / 64])
		&& gen->map->tilemap[y / 64][x / 64] != '1')
		return (0);
	return (1);
}

void	draw_floor(t_general *gen, float draw_start, int i)
{
	while (draw_start < gen->win_y)
		my_mlx_pixel_put(gen->img, i, draw_start++, GREEN_PIXEL);
}

void	draw_ceiling(t_general *gen, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
		my_mlx_pixel_put(gen->img, i, j++, BLUE_PIXEL);
}

void	draw_wall(t_general *gen, float wall_dist, int i, int flag)
{
	float	draw_end;
	float	draw_start;
	float	proj_plane_dis;
	float	proj_column_height;

	proj_plane_dis = (gen->win_x / 2) / ft_tan(gen->pov);
	proj_column_height = ((64 / wall_dist) * proj_plane_dis);
	draw_start = (gen->win_y / 2) - (proj_column_height / 2);
	draw_end = (gen->win_y / 2) + (proj_column_height / 2);
	if (wall_dist < 0 || draw_start < 0 || draw_start > gen->win_y)
		return ;
	draw_ceiling(gen, draw_start, i);
	while (draw_start <= draw_end)
	{
		if (flag == 0)
			my_mlx_pixel_put(gen->img, i, draw_start, RED_PIXEL);
		if (flag == 1)
			my_mlx_pixel_put(gen->img, i, draw_start, ORANGE_PIXEL);
		if (i == gen->win_x / 2)
			my_mlx_pixel_put(gen->img, gen->win_x / 2, draw_start, 0xFFFFFF);
		draw_start++;
	}
	draw_floor(gen, draw_start, i);
}

//Raycast loop. For each ray:
//	- Find wall intersection point
//	- Find distance between player and wall intersection point
//	- Draw line on screen.
int	raycast(t_general *gen, t_ray *ray)
{
	int			i;
	double		hdist;
	double		vdist;
	float		column;

	i = 0;
	column = (float)gen->pov/gen->win_x;
	ray->an = norm(gen->player->an + (gen->pov / 2));
	while (i < gen->win_x)
	{
		vertical_intersection(gen, gen->ray);
		vdist = dist(gen, ray, ray->vy, ray->vx);
		horizontal_intersection(gen, gen->ray);
		hdist = dist(gen, ray, ray->hy, ray->hx);
		if (hdist <= vdist)
			draw_wall(gen, hdist, i, 0);
		else
			draw_wall(gen, vdist, i, 1);
		ray->an = norm(ray->an - column);
		if (i == gen->win_x/2)
		{
			printf("DIR: %f\n", ray->an);
			printf("hx: %f\nhy: %f\n", ray->hx, ray->hy);
			printf("vx: %f\nvy: %f\n", ray->vx, ray->vy);
			printf("HDIST: %f\nVDIST: %f\n", hdist, vdist);
		}
		i++;
	}
	return (0);
}

void	print_display(t_general *gen)
{
	init_img(gen);
	raycast(gen, gen->ray);
	minimap(gen);
	raycast2d(gen);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->img->img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->img->img);
}

//Raycast based on player's direction and pov
int	render(t_general *gen)
{
	if (gen->key->l == 1)
		gen->player->an = norm(gen->player->an - 0.1);
	if (gen->key->r == 1)
		gen->player->an = norm(gen->player->an + 0.1);
	if (gen->key->w == 1)//W
	{
		gen->player->y -= sin(toRad(gen->player->an));
		gen->player->x += cos(toRad(gen->player->an));
	}
	if (gen->key->s == 1)
	{
		gen->player->y -= sin(toRad(norm(gen->player->an + 180)));
		gen->player->x += cos(toRad(norm(gen->player->an + 180)));
	}
	if (gen->key->a == 1)
	{
		gen->player->y -= sin(toRad(norm(gen->player->an + 90)));
		gen->player->x += cos(toRad(norm(gen->player->an + 90)));
	}
	if (gen->key->d == 1)
	{
		gen->player->y -= sin(toRad(norm(gen->player->an - 90)));
		gen->player->x += cos(toRad(norm(gen->player->an - 90)));
	}
	print_display(gen);
	return(0);
} 