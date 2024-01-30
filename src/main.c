/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/30 13:21:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

	game.map = &map;
	game.player = &player;
	game.ray = &ray;

	if (map_check(&map, av))
		return (1);
	init(&game);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.win_x, game.win_y, "cub3d");

	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, input, &game);

	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return(0);
}