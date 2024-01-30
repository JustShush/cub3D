/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/30 13:33:33 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if point is inside the screen
int	point_check(t_game *game, int y, int x)
{
	if (y >= 0 && x >= 0 && y <= game->win_y && x <= game->win_x)
		return (0);
	return (1);
}

//Takes 2 points' y coordinates and returns their distance
double	point_dist(t_game *game, int ay, int by)
{
	double beta;
	double	fix;
	double	dist;

	beta = fabs(game->player->dir - game->ray->angle);
	dist = abs(ay - by) / sin(game->ray->angle * 2 * M_PI/360);
	fix = fabs(dist * cos(beta * 2 * M_PI/360));
	return (fix);
		
}

void		draw_floor(t_game *game, float draw_start, int i)
{
	while (draw_start < game->win_y)
	{
		mlx_pixel_put(game->mlx, game->win, i, draw_start++, GREEN_PIXEL);
	}
}

void		draw_ceiling(t_game *game, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
	{
		mlx_pixel_put(game->mlx, game->win, i, j++, BLUE_PIXEL);
	}
}

void		draw_wall(t_game *game, double wall_dist, int i, int flag)
{
	float	draw_start;
	float	pl_proj_plane_dis;
	float	proj_column_height;

	pl_proj_plane_dis = (game->win_x/2) / tan((game->pov / 2 * 2 * M_PI)/360);
	proj_column_height = (float)((64 / wall_dist) * pl_proj_plane_dis);
	draw_start = ((float)(game->win_y / 2) - (float)(proj_column_height / 2));
	draw_ceiling(game, draw_start, i);
	while (draw_start <= ((float)(game->win_y / 2) + (float)(proj_column_height / 2)))
	{
		if (flag == 0)
			mlx_pixel_put(game->mlx, game->win, i, draw_start, RED_PIXEL);
		if (flag == 1)
			mlx_pixel_put(game->mlx, game->win, i, draw_start, ORANGE_PIXEL);
		draw_start++;
	}
	draw_floor(game, draw_start, i);
}

//Check intersection of ray and horizontal lines
void	horizontal_intersection(t_game *game,  t_ray *ray)
{
	if (ray->angle >= 0 && ray->angle < 180) //If ray is facing up
			ray->ay = round(game->player->y / 64) * (64) - 1;
	else //If ray is facing down
		ray->ay = round(game->player->y / 64) * (64) + 64;
	ray->ax = game->player->x + (float)(game->player->y - ray->ay)/tan((ray->angle * 2 * M_PI)/360);
	while (!point_check(game, ray->ay, ray->ax) && game->map->tilemap[ray->ay/64][ray->ax/64] != '1')
	{
		ray->ax += 64/tan((ray->angle * 2 * M_PI)/360);
		if (ray->angle >= 0 && ray->angle < 180) //If ray is facing up
			ray->ay -= 64;
		else //If ray is facing down
			ray->ay += 64; 
	}
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_game *game, t_ray *ray)
{
	if ((ray->angle < 90 && ray->angle >= 0) || (ray->angle > 270 && ray->angle <= 360)) //If ray is facing right
		ray->ax = round(game->player->x / 64) * (64) + 64;
	else //If ray is facing left
		ray->ax = round(game->player->x / 64) * (64) - 1;
	ray->ay = game->player->y + (float)(game->player->x - ray->ax) * tan((ray->angle * 2 * M_PI)/360);
	while (!point_check(game, ray->ay, ray->ax) && game->map->tilemap[ray->ay/64][ray->ax/64] != '1')
	{
		if (ray->angle > 0 && ray->angle < 180) //If ray is facing up
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
int	raycast(t_game *game, t_ray *ray)
{
	int			i;
	double		hdist;
	double		vdist;
	float		column;

	i = 0;
	ray->angle = game->player->dir - (game->pov / 2);
	column = (float)game->pov/game->win_x;
	while (ray->angle < game->player->dir + (game->pov / 2))
	{
		horizontal_intersection(game, game->ray);
		hdist = point_dist(game, game->player->y, ray->ay);
		vertical_intersection(game, game->ray);
		vdist = point_dist(game, game->player->y, ray->ay);
		if (hdist <= vdist)
			draw_wall(game, hdist, i, 0);
		else
			draw_wall(game, vdist, i, 1);
		ray->angle += column;
		i++;
	}
	return (0);
}

//Raycast based on player's direction and pov
int	render(t_game *game)
{
	raycast(game, game->ray);
	return(0);
}