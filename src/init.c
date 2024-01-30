/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:05 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/30 13:21:43 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Set player's position and direction
//Only handles North for now
void	player_pos(t_game *game, char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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

void	init(t_game *game)
{
	player_pos(game, game->map->tilemap);
	game->pov = 60;
	game->win_x = 320;
	game->win_y = 200;
}