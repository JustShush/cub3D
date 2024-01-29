/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/29 15:09:19 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

# define	M_PI		3.14159265358979323846
# define	RED_PIXEL	0xFF0000

//Set player's position and direction
//Only handles North for now
void	player_pos(t_game *game, char **map, int y, int x)
{
	while (y < game->map->y && x < (int)ft_strlen(game->map->tilemap[y]))
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N')
			{
				game->player->dir = 90;
				game->player->y = (y * 64) + 32;
				game->player->x = (x * 64) + 32;
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

int	point_check(t_game *game, int y, int x)
{
	if (y >= 0 && x >= 0 && y <= game->win_y && x <= game->win_x)
		return (0);
	return (1);
}

//Takes 2 points and returns their distance
double	point_dist(t_game *game, int ay, int ax, int by, int bx)
{
	double	distorted;
	(void)game;
	//Switch to cos() and sin() for better preformence
	distorted = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
	return (distorted);
		
}

void		draw_wall(t_game *game, double wall_dist)
{
	float	draw_start;
	float	pl_proj_plane_dis;
	float	proj_column_height;

	pl_proj_plane_dis = (game->win_x/2) / tan((game->pov / 2 * 2 * M_PI)/360);
	proj_column_height = (float)((64 / wall_dist) * pl_proj_plane_dis);
	draw_start = ((float)(game->win_y / 2) - (float)(proj_column_height / 2));
	/* while (draw_start <= ((float)(game->win_y / 2) + (float)(proj_column_height / 2)))
	{
		mlx_pixel_put(game->mlx, game->win, game->ray->angle, draw_start, RED_PIXEL);
		draw_start++;
	} */
	mlx_pixel_put(game->mlx, game->win, game->ray->angle, draw_start, RED_PIXEL);
}

//Check intersection of ray and horizontal lines
void	horizontal_intersection(t_game *game,  t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < 180) //If ray is facing up
			ray->ay = round(game->player->y / 64) * (64) - 1;
		else //If ray is facing down
			ray->ay = round(game->player->y / 64) * (64) + 64;
		ray->ax = game->player->x + (float)(game->player->y - ray->ay)/tan((ray->angle * 2 * M_PI)/360);
		while (!point_check(game, ray->ay, ray->ax) && game->map->tilemap[ray->ay/64][ray->ax/64] != '1')
		{
			ray->ax += 64/tan((ray->angle * 2 * M_PI)/360);
			if (ray->angle > 0 && ray->angle < 180) //If ray is facing up
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
//Sorry for monstrosity
int	raycast(t_game *game, t_ray *ray)
{
	double		hdist;
	double		vdist;
	float		column;

	ray->angle = 0;
	column = (float)game->pov/game->win_x;
	while (ray->angle < game->win_x)
	{
		horizontal_intersection(game, game->ray);
		hdist = point_dist(game, game->player->y, game->player->x, ray->ay, ray->ax);
		vertical_intersection(game, game->ray);
		vdist = point_dist(game, game->player->y, game->player->x, ray->ay, ray->ax);
		if (hdist < vdist)
			draw_wall(game, hdist);
		else
			draw_wall(game, vdist);
		ray->angle += column;
	}
	return (0);
}

//Get player's coordinates
//Get player's direction
//Raycast based on player's direction and pov
int	render(t_game *game)
{
	raycast(game, game->ray);
	return(0);
}

//What the program does:
// - Checks for correct arguments;
// - Initializes a map struct and it's tilemap array and (N,S,W,E) strings.
// - Opens a window with a pixel at the center;
// - Exits cleanly with ESC and Window X button;
int	main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nIncorrect ammount of arguments\n"));

	t_map		map;
	t_ray		ray;
	t_game		game;
	t_player	player;

	if (map_check(&map, av))
		return (1);
	game.map = &map;
	game.player = &player;
	game.ray = &ray;
	game.pov = 60;
	game.win_x = 320;
	game.win_y = 200;
	
	player_pos(&game, map.tilemap, 0, 0);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.win_x, game.win_y, "cub3d");

	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, esc_key, &game);

	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return(0);
}