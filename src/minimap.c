/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:16:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/06 15:46:12 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int sizeofmap_x(t_general *gen)
{
	int i;
	int j;
	int res;

	res = 0;
	i = 0;
	while(gen->map->tilemap[i])
	{
		j = 0;
		while(gen->map->tilemap[i][j])
			j++;
		if(j > res)
			res = j;
		i++;
	}
	return (i);
}

int sizeofmap_y(t_general *gen)
{
	int i = 0;

	while(gen->map->tilemap[i])
	{
		i++;
	}
	return (i - 1);
}

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

void	draw_player(t_general *gen)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = gen->player->an + 30;
	x = gen->player->x * SCALE / 64;
	y = (gen->player->y * SCALE / 64);
	while (j > gen->player->an - 30)
	{
		i = 0;
		while (i < SCALE)
		{
			my_mlx_pixel_put(gen->img, x - (cos(toRad(j)) * i), y - (sin(toRad(j) ) * i), GREEN_PIXEL);
			i++;
		}
		j--;
	}
	my_mlx_pixel_put(gen->img, x, y, ORANGE_PIXEL);
}

void	mini_ray(t_general *gen, t_ray *ray)
{
	my_mlx_pixel_put(gen->img, (ray->hx * SCALE / 64) + (sign(gen->player->an, 0)), (ray->hy * SCALE / 64) + (sign(gen->player->an, 1)), BLUE_PIXEL);
	my_mlx_pixel_put(gen->img, (ray->vx * SCALE / 64) + (sign(gen->player->an, 0)), ((ray->vy * SCALE / 64) + SCALE * 15) + (sign(gen->player->an, 1)), BLUE_PIXEL);
}

int	minimap(t_general *gen)
{
	int y = 0;
	int x = 0;
	int map_x = 0;
	int map_y = 0;

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