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

void	draw_player(t_general *gen)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = gen->player->an + 30;
	x = gen->player->x * 20 / 64;
	y = (gen->player->y * 20 / 64) + 300;
	while (j > gen->player->an - 30)
	{
		i = 0;
		while (i < 20)
		{
			mlx_pixel_put(gen->mlx, gen->win, x - (cos(toRad(j)) * i), y - (sin(toRad(j) ) * i), GREEN_PIXEL);
			i++;
		}
		j--;
	}
	mlx_pixel_put(gen->mlx, gen->win, x, y, ORANGE_PIXEL);
}

void	mini_ray(t_general *gen, t_ray *ray)
{
	mlx_pixel_put(gen->mlx, gen->win, (ray->hx * 20 / 64) + (sign(gen->player->an, 0)), (ray->hy * 20 / 64) + (sign(gen->player->an, 1)), BLUE_PIXEL);
	mlx_pixel_put(gen->mlx, gen->win, (ray->vx * 20 / 64) + (sign(gen->player->an, 0)), ((ray->vy * 20 / 64) + 300) + (sign(gen->player->an, 1)), BLUE_PIXEL);
}

int	minimap(t_general *gen)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = gen->win_y - 100;
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