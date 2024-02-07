/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:16:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/07 15:15:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_square(t_general *gen, int y, int x, int color)
{
	int	j = 0;
	int	i = 0;

	while (j < 20)
	{
		i = 0;
		while (i < 20)
		{
			if (j == 0 || i == 0)
				mlx_pixel_put(gen->mlx, gen->win, x + i, y + j, 0x000000);
			else
				mlx_pixel_put(gen->mlx, gen->win, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

//Takes player position and angle and ray lenght. Shoots ray
void	put_rays(t_general *gen, int angle, int py, int px, int len)
{
	int	i;
	int	rx;
	int	ry;
	
	i = 0;
	while (i < len)
	{
		rx = round(px - (cos(toRad(angle)) * i));
		ry = round(py - (sin(toRad(angle)) * i));
		mlx_pixel_put(gen->mlx, gen->win, rx, ry, GREEN_PIXEL);
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
	mlx_pixel_put(gen->mlx, gen->win, px, py, ORANGE_PIXEL);
	while (i <= 360)
	{
		j = r;
		while (j > 0)
		{
			x = round(px + (j * cos(toRad(i))));
			y = round(py + (j * sin(toRad(i))));
			mlx_pixel_put(gen->mlx, gen->win, x, y, ORANGE_PIXEL);
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
	int	ray_len;

	pradius = 2;
	ray_len = 50;
	i = gen->player->an + (gen->pov / 2);
	x = gen->player->x * 20 / 64;
	y = (gen->player->y * 20 / 64) + 300;
	while (i > gen->player->an - (gen->pov / 2))
		put_rays(gen, i--, y, x, ray_len);
	put_player(gen, y, x, pradius);
}

int	minimap(t_general *gen)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = gen->win_y - 100;
	raycast2d(gen);
	while (j < gen->win_y && k < 100)
	{
		i = 0;
		while (i < 120)
		{
			if (gen->map->tilemap[k / 20][i / 20] == '1')
				put_square(gen, j, i, RED_PIXEL);
			i += 20;
		}
		k += 20;
		j += 20;
	}
	return (0);
}