/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/30 12:36:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_key(int key, t_game *game)
{
	if (key == 65307)
		close_game(game);
	return (0);
}

int	input(int key, t_game *game)
{
	esc_key(key, game);
	if (key == 100 && game->map->tilemap[game->player->y / 64][(game->player->x + 1)
		/ 64] != '1')
		game->player->x += 1;
	if (key == 97 && game->map->tilemap[game->player->y / 64][(game->player->x - 1)
		/ 64] != '1')
		game->player->x -= 1;
	if (key == 115 && game->map->tilemap[(game->player->y + 1) / 64][game->player->x
		/ 64] != '1' )
		game->player->y += 1;
	if (key == 119 && game->map->tilemap[(game->player->y - 1) / 64][game->player->x
		/ 64] != '1')
		game->player->y -= 1;
	if (key == 65363)
	{
		if (game->player->dir == 360)
			game->player->dir = 0;
		else
			game->player->dir += 1;
	}
	if (key == 65361)
	{
		if (game->player->dir == 0)
			game->player->dir = 360;
		else
			game->player->dir -= 1;
	}
	return (0);
}
