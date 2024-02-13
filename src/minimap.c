/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:16:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/13 13:01:10 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_square(t_general *gen, int y, int x, int color)
{
	int	j = 0;
	int	i = 0;

	while (j < SCALE)
	{
		i = 0;
		while (i < SCALE)
		{
			if (j == 0 || i == 0)
				my_mlx_pixel_put(gen->img, x + i, y + j, 0x000000);
			else
				my_mlx_pixel_put(gen->img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

//Takes player position and angle and ray length. Shoots ray
void	put_rays(t_general *gen, int angle, int py, int px)
{
	int	i;
	int	rx;
	int	ry;
	
	i = 0;
	while (i < SCALE * 3)
	{
		rx = round(px - (sin(toRad(angle - 90)) * i));
		ry = round(py - (cos(toRad(angle - 90)) * i));
		if (rx >= 0 && ry >= 0 && rx <= gen->win_x && ry <= gen->win_y)
			my_mlx_pixel_put(gen->img, rx, ry, RED_PIXEL);
		i++;
	}
}

//Takes player position and radius. Draws circle
void	put_player(t_general *gen, int py, int px, int r)
{
	int	i;
	int	j;
	int	x;
	int	y;
	
	i = 0;
	if (px >= 0 && py >= 0 && px <= gen->win_x && py <= gen->win_y)
		my_mlx_pixel_put(gen->img, px, py, ORANGE_PIXEL);
	while (i <= 360)
	{
		j = r;
		while (j > 0)
		{
			x = round(px + (j * cos(toRad(i))));
			y = round(py + (j * sin(toRad(i))));
			if (x >= 0 && y >= 0 && x <= gen->win_x && py <= gen->win_y)
				my_mlx_pixel_put(gen->img, x, y, ORANGE_PIXEL);
			j--;
		}
		i += 1;
	}

}

//Casts rays for minimap and puts player
void	raycast2d(t_general *gen)
{
	int	i;
	int	x;
	int	y;
	int	pradius;

	pradius = 2;
	i = gen->player->an;
	x = gen->player->x * SCALE / 64;
	y = (gen->player->y * SCALE / 64);
	if (i >= gen->player->an - (gen->pov / 2))
		put_rays(gen, i--, y, x);
	put_player(gen, y, x, pradius);
}

int	minimap(t_general *gen)
{
	int y = 0;
	int x = 0;
	int map_x = 0;
	int map_y = 0;

	raycast2d(gen);
	while(gen->map->tilemap[y] && map_y <= gen->map_height && map_x <= gen->map_width)
	{
		while(gen->map->tilemap[y][x] && map_y <= gen->map_height && map_x <= gen->map_width && gen->map->tilemap[y][x] != '\n')
		{
			if(gen->map->tilemap[y][x] == '1')
				put_square(gen, map_y, map_x, 0x00000FFF);
			else if(gen->map->tilemap[y][x] == '0')
				put_square(gen, map_y, map_x, 0x00FFF000);
			else if(gen->map->tilemap[y][x] == 'W' || gen->map->tilemap[y][x] == 'E' || gen->map->tilemap[y][x] == 'N' || gen->map->tilemap[y][x] == 'S')
				put_square(gen, map_y, map_x, 0x00FFF000);
			else if(gen->map->tilemap[y][x] == ' ' || gen->map->tilemap[y][x] == '\t')
				put_square(gen, map_y, map_x, 0x000000FF);
			map_x += SCALE;
			x++;
		}
		map_y += SCALE;
		map_x = 0;
		x = 0;
		y++;
	}
	return (0);
}