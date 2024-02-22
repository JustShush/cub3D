/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:33:58 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:34:53 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	loop_player_pos(t_general *gen, int x, int y, char **map)
{
	if (map[y][x] == 'N')
		gen->player->an = 90;
	if (map[y][x] == 'S')
		gen->player->an = 270;
	if (map[y][x] == 'W')
		gen->player->an = 180;
	if (map[y][x] == 'E')
		gen->player->an = 0;
	if (map[y][x] == 'N' || map[y][x] == 'E' ||
		map[y][x] == 'W' || map[y][x] == 'S')
	{
		gen->player->y = (y * CUB) + (CUB / 2);
		gen->player->x = (x * CUB) + (CUB / 2);
		return (1);
	}
	return (0);
}

//Set player's position and direction
void	player_pos(t_general *gen, char **map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < gen->map->y && x < (int)ft_strlen(gen->map->tilemap[y]))
	{
		while (map[y][x])
		{
			if (loop_player_pos(gen, x, y, map) == 1)
				return ;
			x++;
		}
		x = 0;
		y++;
	}
}
