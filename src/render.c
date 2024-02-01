/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/01 14:04:26 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Returns 0 if point is valid
int	point_check(t_game *game, int y, int x)
{
	if (y >= 0 && x >= 0 && y < game->win_y && x < game->win_x 
		&& game->ray->ay/64 < game->map->y
		&& game->ray->ax/64 < (int)ft_strlen(game->map->tilemap[game->ray->ay/64])
		&& game->map->tilemap[game->ray->ay/64][game->ray->ax/64] != '1')
		return(0);
	return (1);
}

//Takes 2 points' y coordinates and returns their distance
double	point_dist(t_game *game, int ay, int by)
{
	double beta;
	double	fix;
	double	dist;

	beta = fabs(game->player->dir - game->ray->angle);
	dist = abs(ay - by) / sin(game->ray->angle * M_PI / 180);
	fix = fabs(dist * cos(beta * M_PI / 180));
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

	if (wall_dist <= 0)
		return ;
	pl_proj_plane_dis = (game->win_x/2) / tan(game->pov / 2 * M_PI / 180);
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
	if (ray->angle >= 0 && ray->angle < 180) //Facing up
		ray->ay = round(game->player->y / 64) * (64) - 1;
	else //Facing Down
		ray->ay = round(game->player->y / 64) * (64) + 64;
	ray->ax = game->player->x + (float)(game->player->y - ray->ay) / tan((ray->angle * M_PI) / 180);
	while (!point_check(game, ray->ay, ray->ax))
	{
		ray->ax += 64 / tan((ray->angle * M_PI) / 180);
		if (ray->angle >= 0 && ray->angle <= 180) //Facing up
			ray->ay -= 64;
		else //Facing down
			ray->ay += 64;
	}
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_game *game, t_ray *ray)
{
	if (ray->angle > 90 && ray->angle <= 270) //Facing left
		ray->ax = round(game->player->x / 64) * (64) - 1;
	else //Facing right
		ray->ax = round(game->player->x / 64) * (64) + 64;
	ray->ay = game->player->y + (float)(game->player->x - ray->ax) * tan((ray->angle * M_PI) / 180);
	while (!point_check(game, ray->ay, ray->ax))
	{
		ray->ay += 64 * tan((ray->angle * M_PI) / 180);
		if (ray->angle >= 90 && ray->angle <= 270) //Facing left
			ray->ax -= 64;
		else //Facing right
			ray->ax += 64;
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
	hdist = 0;
	vdist = 0;
	column = (float)game->pov/game->win_x;
	ray->angle = game->player->dir + (game->pov / 2);
	while (i <= game->win_x && ray->angle >= game->player->dir - (game->pov / 2))
	{
		horizontal_intersection(game, game->ray);
		hdist = point_dist(game, game->player->y, ray->ay);
		vertical_intersection(game, game->ray);
		vdist = point_dist(game, game->player->y, ray->ay);
		if (hdist <= vdist)
			draw_wall(game, hdist, i, 0);
		else
			draw_wall(game, vdist, i, 1);
		ray->angle = norm(ray->angle - column);
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