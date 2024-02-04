/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/04 13:25:14 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if point is inside the screen
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 && y < gen->win_y && x < gen->win_x 
		&& y / 64 < gen->map->y 
		&& x / 64 < ft_strlen(gen->map->tilemap[y / 64])
		&& gen->map->tilemap[y / 64][x / 64] != '1')
		return (0);
	return (1);
}

//Takes 2 points' y coordinates and returns their distance
float	dist(t_general *gen, t_ray *ray, int y, int x)
{
	float	beta;
	float	fix;
	float	dist;

	dist = (cos(toRad(ray->an))*(x - gen->player->x)) - (sin(toRad(ray->an))*(y - gen->player->y));
	beta = norm(gen->player->an - ray->an);
	fix = dist * cos(toRad(beta));
	return (fix);
}

void	draw_floor(t_general *gen, float draw_start, int i)
{
	while (draw_start < gen->win_y)
	{
		mlx_pixel_put(gen->mlx, gen->win, i, draw_start++, GREEN_PIXEL);
	}
}

void	draw_ceiling(t_general *gen, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
	{
		mlx_pixel_put(gen->mlx, gen->win, i, j++, BLUE_PIXEL);
	}
}

void	draw_wall(t_general *gen, double wall_dist, int i, int flag)
{
	float	draw_start;
	float	pl_proj_plane_dis;
	float	proj_column_height;

	pl_proj_plane_dis = (gen->win_x/2) / tan(toRad(gen->pov));
	proj_column_height = (float)((64 / wall_dist) * pl_proj_plane_dis);
	draw_start = ((float)(gen->win_y / 2) - (float)(proj_column_height / 2));
	if (wall_dist < 0 || draw_start < 0 || draw_start > gen->win_y)
		return ;
	draw_ceiling(gen, draw_start, i);
	while (draw_start <= ((float)(gen->win_y / 2) + (float)(proj_column_height / 2)))
	{
		if (flag == 0)
			mlx_pixel_put(gen->mlx, gen->win, i, draw_start, RED_PIXEL);
		if (flag == 1)
			mlx_pixel_put(gen->mlx, gen->win, i, draw_start, ORANGE_PIXEL);
		draw_start++;
	}
	draw_floor(gen, draw_start, i);
}

//Check intersection of ray and horizontal lines
void	horizontal_intersection(t_general *gen, t_ray *ray)
{
	int	i;
	int	by;
	int	bx;

	i = 0;
	by = 0;
	bx = 0;
	if (ray->an == 0 || ray->an == 180)
	{
		ray->hx = gen->player->x;
		ray->hy = gen->player->y;
		i = 8;
	}
	else if (sin(toRad(ray->an)) > 0.001) //If ray is facing up
	{	
		ray->hy = round(gen->player->y / 64) * (64) - 0.001;
		ray->hx = round(gen->player->x + (float)(gen->player->y - ray->hy) / tan(toRad(ray->an)));
		by = -64;
		bx = 64 / tan(toRad(ray->an));
	}
	else //If ray is facing down
	{
		ray->hy = round(gen->player->y / 64) * (64) + 64;
		ray->hx = round(gen->player->x + (float)(gen->player->y - ray->hy) / tan(toRad(ray->an)));
		by = 64;
		bx = -64 / tan(toRad(ray->an));
	}
	while (i < 8 && !point_check(gen, ray->vy, ray->vx))
	{
		ray->hx += bx;
		ray->hy += by;
		i++;
	}
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_general *gen, t_ray *ray)
{
	int	i;
	int	by;
	int	bx;

	i = 0;
	by = 0;
	bx = 0;
	if (ray->an == 90 || ray->an == 270 || ray->an == 360)
	{
		ray->vx = gen->player->x;
		ray->vy = gen->player->y;
		i = 8;
	}
	else if ((cos(toRad(ray->an)) > 0.001)) //If ray is facing left
	{
		ray->vx = round(gen->player->x / 64) * (64) + 64;
		ray->vy = round(gen->player->y + (float)(gen->player->x - ray->vx) * tan(toRad(ray->an)));
		bx = -64;
		by = (64) / tan(toRad(ray->an));
	}
	else if ((cos(toRad(ray->an)) < -0.001)) //If ray is facing right
	{
		ray->vx = round(gen->player->x / 64) * (64) - 0.001;
		ray->vy = round(gen->player->y + (float)(gen->player->x - ray->vx) * tan(toRad(ray->an)));
		bx = 64;
		by = -64 / tan(toRad(ray->an));
	}
	while (i < 8 && !point_check(gen, ray->vy, ray->vx))
	{
		ray->vx += bx;
		ray->vy += by;
		i++;
	}
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
		horizontal_intersection(gen, gen->ray);
		hdist = dist(gen, ray, ray->hy, ray->hx);
		vertical_intersection(gen, gen->ray);
		vdist = dist(gen, ray, ray->vy, ray->vx);
		if (hdist <= vdist)
			draw_wall(gen, hdist, i, 0);
		else
			draw_wall(gen, vdist, i, 1);
		ray->an = norm(ray->an - column);
		i++;
	}
	return (0);
}

//Raycast based on player's direction and pov
int	render(t_general *gen)
{
	raycast(gen, gen->ray);
	return(0);
}