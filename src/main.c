/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 15:53:06 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define RED_PIXEL 0xFF0000

int	render_frames(t_game *game)
{
	mlx_pixel_put(game->mlx, game->win, 360, 240, RED_PIXEL);
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

	if (map_check(&map, av))
		return (1);
	
	game.map = &map;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 720, 480, "cub3d");

	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, esc_key, &game);

	mlx_loop_hook(game.mlx, render_frames, &game);
	mlx_loop(game.mlx);
	return(0);
}