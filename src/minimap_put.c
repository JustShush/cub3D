/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:35:45 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:36:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_square(t_general *gen, int y, int x, int color)
{
	int	j;
	int	i;

	j = 0;
	while (j < SCALE)
	{
		i = 0;
		while (i < SCALE)
		{
			if (j == 0 || i == 0)
				my_mlx_pixel_put(gen, x + i, y + j, 0x000000);
			else
				my_mlx_pixel_put(gen, x + i, y + j, color);
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
		rx = round(px - (sin(to_rad(angle - 90)) * i));
		ry = round(py - (cos(to_rad(angle - 90)) * i));
		if (rx >= 0 && ry >= 0 && rx <= gen->win_x && ry <= gen->win_y)
			my_mlx_pixel_put(gen, rx, ry, RED_PIXEL);
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
		my_mlx_pixel_put(gen, px, py, ORANGE_PIXEL);
	while (i <= 360)
	{
		j = r;
		while (j > 0)
		{
			x = round(px + (j * cos(to_rad(i))));
			y = round(py + (j * sin(to_rad(i))));
			if (x >= 0 && y >= 0 && x <= gen->win_x && py <= gen->win_y)
				my_mlx_pixel_put(gen, x, y, ORANGE_PIXEL);
			j--;
		}
		i += 1;
	}
}

void	put_map(t_general *gen, int *num)
{
	if (gen->map->tilemap[num[0]][num[1]] == '1')
		put_square(gen, num[3], num[2], 0x00000FFF);
	else if (gen->map->tilemap[num[0]][num[1]] == '0')
		put_square(gen, num[3], num[2], 0x00FFF000);
	else if (gen->map->tilemap[num[0]][num[1]] == 'W'
		|| gen->map->tilemap[num[0]][num[1]] == 'E'
			|| gen->map->tilemap[num[0]][num[1]] == 'N'
				|| gen->map->tilemap[num[0]][num[1]] == 'S')
		put_square(gen, num[3], num[2], 0x00FFF000);
	else if (gen->map->tilemap[num[0]][num[1]] == ' '
		|| gen->map->tilemap[num[0]][num[1]] == '\t')
		put_square(gen, num[3], num[2], 0x000000FF);
}
