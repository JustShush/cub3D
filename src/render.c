/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/01 10:51:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if point is inside the screen
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 && y < gen->win_y && x < gen->win_x 
		&& gen->ray->ay/64 < gen->map->y 
		&& gen->ray->ax/64 < ft_strlen(gen->map->tilemap[gen->ray->ay/64])
		&& gen->map->tilemap[gen->ray->ay/64][gen->ray->ax/64] != '1')
		return (0);
	return (1);
}

//Takes 2 points' y coordinates and returns their distance
double	point_dist(t_general *gen, int ay, int by)
{
	double beta;
	double	fix;
	double	dist;

	beta = fabs(gen->player->dir - gen->ray->angle);
	dist = abs(ay - by) / sin(gen->ray->angle * M_PI / 180);
	fix = fabs(dist * cos(beta * M_PI / 180));
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

	pl_proj_plane_dis = (gen->win_x/2) / tan(gen->pov / 2 * M_PI / 180);
	proj_column_height = (float)((64 / wall_dist) * pl_proj_plane_dis);
	draw_start = ((float)(gen->win_y / 2) - (float)(proj_column_height / 2));
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
	if (ray->angle >= 0 && ray->angle <= 180) //If ray is facing up
		ray->ay = round(gen->player->y / 64) * (64) - 1;
	else //If ray is facing down
		ray->ay = round(gen->player->y / 64) * (64) + 64;
	ray->ax = round(gen->player->x + (float)(gen->player->y - ray->ay)/tan((ray->angle * 2 * M_PI)/360));
	while (!point_check(gen, ray->ay, ray->ax))
	{
		ray->ax += round(64/tan((ray->angle * 2 * M_PI)/360));
		if (ray->angle > 0 && ray->angle <= 180) //If ray is facing up
			ray->ay -= 64;
		else //If ray is facing down
			ray->ay += 64;
	}
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_general *gen, t_ray *ray)
{
	if ((ray->angle < 90 && ray->angle >= 0) || (ray->angle > 270 && ray->angle <= 360)) //If ray is facing right
		ray->ax = round(gen->player->x / 64) * (64) + 64;
	else //If ray is facing left
		ray->ax = round(gen->player->x / 64) * (64) - 1;
	ray->ay = round(gen->player->y + (float)(gen->player->x - ray->ax) * tan((ray->angle * 2 * M_PI)/360));
	while (!point_check(gen, ray->ay, ray->ax))
	{
		if (ray->angle >= 0 && ray->angle <= 180) //If ray is facing up
			ray->ay -= 64;
		else //If ray is facing down
			ray->ay += 64; 
		if ((ray->angle >= 0 && ray->angle < 90) || (ray->angle > 270 && ray->angle <= 360)) //If ray is facing right
			ray->ax += 64;
		else //If ray is facing left
			ray->ax -= 64;
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
	ray->angle = gen->player->dir + (gen->pov / 2);
	while (i <= gen->win_x && ray->angle >= gen->player->dir - (gen->pov / 2))
	{
		horizontal_intersection(gen, gen->ray);
		hdist = point_dist(gen, gen->player->y, ray->ay);
		vertical_intersection(gen, gen->ray);
		vdist = point_dist(gen, gen->player->y, ray->ay);
		if (hdist <= vdist)
			draw_wall(gen, hdist, i, 0);
		else
			draw_wall(gen, vdist, i, 1);
		ray->angle = norm(ray->angle - column);
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