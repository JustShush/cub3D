/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/25 15:07:51 by ddiniz-m         ###   ########.fr       */
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

//Checks if point corresponds with a wall(1) tile
//Puts pixel for now
int	check_wall(t_game *game, int ay, int ax)
{	
	if (game->map->tilemap[ay/64][ax/64] == '1') // is wall
	{
		mlx_pixel_put(game->mlx, game->win, ax, ay, RED_PIXEL);
		return (1);
	}
	return (0);
}

//Raycast loop. For each ray:
//	- Find wall intersection point
//	- Find distance between player and wall intersection point
//	- Draw line on screen.
//Sorry for monstrosity
int	raycast(t_game *game)
{
	int		ax;
	int		ay;
	float	column;
	float	ray_angle;
	int		pl_proj_plane_dis;
	

	column = (float)game->pov/game->win_x;
	ray_angle = game->player->dir - (game->pov / 2); //if pov 60 and pdir=90 fisrt ray_angle is 60
	pl_proj_plane_dis = (game->win_x/2) / tan((game->pov / 2 * 2 * M_PI)/360);
	while (ray_angle < game->player->dir + (game->pov / 2)) //if pov 60 and pdir=90 last ray_angle is 120
	{
		//Check intersection of ray and horizontal lines
		if (ray_angle > 0 && ray_angle < 180) //If ray is facing up
			ay = round(game->player->y / 64) * (64) - 1;
		else //If ray is facing down
			ay = round(game->player->y / 64) * (64) + 64;
		ax = game->player->x + (float)(game->player->y - ay)/tan((ray_angle * 2 * M_PI)/360);
		while (check_wall(game, ay, ax) == 0)
		{
			ax += 64/tan((ray_angle * 2 * M_PI)/360);
			if (ray_angle > 0 && ray_angle < 180) //If ray is facing up
				ay -= 64;
			else //If ray is facing down
				ay += 64; 
		}
		//Check intersection of ray and vertical lines
		if ((ray_angle < 90 && ray_angle > 0) || (ray_angle > 270 && ray_angle < 360)) //If ray is facing right
			ax = round(game->player->x / 64) * (64) + 64;
		else //If ray is facing left
			ax = round(game->player->x / 64) * (64) - 1;
		ay = game->player->y + (float)(game->player->x - ax) * tan((ray_angle * 2 * M_PI)/360);
		while (ay > 0 && check_wall(game, ay, ax) == 0)
		{
			if (ray_angle > 0 && ray_angle < 180) //If ray is facing up
				ay -= 64;
			else //If ray is facing down
				ay += 64; 
			if ((ray_angle > 0 && ray_angle < 90) || (ray_angle > 270 && ray_angle < 360)) //If ray is facing right
				ax += 64;
			else //If ray is facing left
				ax -= 64;
		}
		ray_angle += column;
	}
	return (0);
}

//Get player's coordinates
//Get player's direction
//Raycast based on player's direction and pov
int	render(t_game *game)
{
	raycast(game);
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