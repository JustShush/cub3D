/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:05 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/04 13:07:53 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Set player's position and direction
//Only handles North for now
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
			if (map[y][x] == 'N')
				gen->player->an = 90;
			if (map[y][x] == 'S')
				gen->player->an = 270;
			if (map[y][x] == 'W')
				gen->player->an = 180;
			if (map[y][x] == 'E')
				gen->player->an = 0;
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W' || map[y][x] == 'S')
			{
				gen->player->y = (y * 64) + 32;
				gen->player->x = (x * 64) + 32;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

t_general	*init(t_general *gen, char **av)
{
	t_ray ray;
	gen = (t_general *)malloc(sizeof(t_general));
	gen->textures = (t_textures *)malloc(sizeof(t_textures));
	gen->textures->C = (t_RGB *)malloc(sizeof(t_RGB));
	gen->textures->F = (t_RGB *)malloc(sizeof(t_RGB));
	gen->map = (t_map *)malloc(sizeof(t_map));
	gen->player = (t_player *)malloc(sizeof(t_player));
	gen->ray = &ray;
	gen->file = map_init(av[1]);
	tilemap(gen->map, av[1]);
/* 	printf("\n");
	printf("\nFILE\n");
	printf_array(gen->file);
	printf("\n\nTILEMAP\n\n");
	printf_array(gen->map->tilemap);
	printf("\n\n"); */
	gen->pov = 60;
	gen->win_x = 640;
	gen->win_y = 400;
	gen->ray->an = 0;
	return (gen);
}