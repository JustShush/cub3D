/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/24 18:15:36 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define RED_PIXEL 0xFF0000

void	player_pos(t_game *game, char **map, int y, int x)
{
	while (y < game->map->y && x < (int)ft_strlen(game->map->tilemap[y]))
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N')
			{
				game->ray->dir = 90;
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

int	raycast(t_game *game)
{
	int			i;
	int			point_x;
	int			point_y;
	int			y;
	int			x;

	i = 0;
	point_x = 0;
	point_y = 0;
	y = game->player->y;
	x = game->player->x;
	if (game->ray->dir == 0)
		game->ray->dir = 330;
	game->ray->dir = game->pov - 30;
	while (game->ray->dir <= game->pov)
	{
		while (x > 0 && y > 0 && x > game->map->x && y > game->map->y)
		{
			if (x % 64 == 0 || y % 64 == 0)
			{
				game->ray->wall_dist = sqrt(pow(game->player->y, 2) + pow(x - game->player->x, 2));
				printf("game->ray->wall_dist: %i\n", game->ray->wall_dist);
				if (game->map->tilemap[point_y / 64][point_x / 64] == '1')
				{
					//draw wall
					mlx_pixel_put(game->mlx, game->win, point_x, point_y, RED_PIXEL);
				}
			}
			x++;
			y++;
		}
		game->ray->dir++;
	}
	return (0);
}

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

	t_game	game;
	t_map	map;
	t_player player;
	t_ray	ray;

	if (map_check(&map, av))
		return (1);
	game.map = &map;
	game.player = &player;
	game.ray = &ray;
	game.pov = 60;
	game.win_x = 1024;
	game.win_y = 704;
	
	player_pos(&game, map.tilemap, 0, 0);
	printf("Player Y: %i; Player X: %i\n", game.player->y, game.player->x);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.win_x, game.win_y, "cub3d");

	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, esc_key, &game);

	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return(0);
}