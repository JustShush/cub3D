/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 11:37:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define RED_PIXEL 0xFF0000

int	render_frames(t_game *game)
{
	mlx_pixel_put(game->mlx, game->win, 360, 240, RED_PIXEL);
	return(0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Error\nIncorrect ammount of arguments\n"));
	if (map_check(av))
		return (1);

	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 720, 480, "cub3d");

	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, esc_key, &game);

	mlx_loop_hook(game.mlx, render_frames, &game);
	mlx_loop(game.mlx);
	return(0);
}