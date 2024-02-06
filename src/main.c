/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/06 15:15:50 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	minimap(t_general *gen);

//What the program does:
// - Checks for correct arguments;
// - Initializes a map struct and it's tilemap array and (N,S,W,E) strings.
// - Opens a window with a pixel at the center;
// - Exits cleanly with ESC and Window X button;
int	main(int ac, char **av)
{
	t_general	*gen;

	gen = NULL;
	if (ac != 2)
		return (printf("Error\nIncorrect ammount of arguments\n"));
	
	gen = init(gen, av);
	gen->mlx = mlx_init();

	if(check_map(gen) == 0)
		return 0;
	
	player_pos(gen, gen->map->tilemap);
	printf("PLAYER Y:%f\n", gen->player->y);
	printf("PLAYER X:%f\n", gen->player->x);

	gen->mlx = mlx_init();
	gen->win = mlx_new_window(gen->mlx, gen->win_x, gen->win_y, "cub3d");

	mlx_hook(gen->win, 17, 0, close_game, gen);
	mlx_hook(gen->win, 2, 1L << 0, key_press, gen);
	mlx_hook(gen->win, 3, 1L << 1, key_release, gen);

	//mlx_loop_hook(gen->mlx, minimap, gen);
	mlx_loop_hook(gen->mlx, render, gen);
	mlx_loop(gen->mlx);
	return(0);
}