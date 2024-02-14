/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:54 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/14 12:48:10 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	minimap(t_general *gen);

//What the program does:
// - Checks for correct arguments;
// - Initializes a map struct and it's tilemap array and (N,S,W,E) strings.
// - Opens a window with a pixel at the center;
// - Exits cleanly with ESC and Window X button;

void	look_left(t_general *gen, int sens)
{
	gen->player->an -= 0.01f * sens;
}

void	look_right(t_general *gen, int sens)
{
	gen->player->an += 0.01f * sens;
}

int	mouse_move(int x, int y, t_general *gen)
{
	(void)y;
	if (x != gen->win_x/2 || y != gen->win_y/2)
	{
		if (x > gen->win_x/2)
			look_left(gen, (x - gen->win_x/2) * X_SENSE);
		else if (x < gen->win_x/2)
			look_right(gen, (gen->win_x/2 - x) * X_SENSE);
	}
	mlx_mouse_move(gen->mlx, gen->win, gen->win_x/2, gen->win_y/2);
	return (0);
}

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

	gen->mlx = mlx_init();
	gen->win = mlx_new_window(gen->mlx, gen->win_x, gen->win_y, "cub3d");

	mlx_hook(gen->win, 17, 0, close_game, gen);
	mlx_hook(gen->win, 2, 1L << 0, key_press, gen);
	mlx_hook(gen->win, 3, 1L << 1, key_release, gen);
	mlx_hook(gen->win, 6, 1L << 6, mouse_move, gen);
	mlx_mouse_hide(gen->mlx, gen->win);

	mlx_loop_hook(gen->mlx, render, gen);
	mlx_loop(gen->mlx);
	return(0);
}