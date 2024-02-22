/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:40:41 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:59:09 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	display_position(t_general *gen)
{
	char	*x;
	char	*y;

	x = ft_itoa(gen->player->x);
	y = ft_itoa(gen->player->y);
	mlx_string_put(gen->mlx, gen->win, 10, 20, 0xFFFFFF, "Player position:");
	mlx_string_put(gen->mlx, gen->win, 10, 40, 0xFFFFFF, x);
	mlx_string_put(gen->mlx, gen->win, 10, 60, 0xFFFFFF, y);
	free(x);
	free(y);
}

void	make_wheel(t_general *gen, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 640)
		{
			if ((int)get_pixel_img(&gen->anim[index], j, i) != -16777216
				&& (int)get_pixel_img(&gen->anim[index], j, i) != 0)
			{
				my_mlx_pixel_put(gen, j + gen->win_x / 2 - 320,
					i + gen->win_y - 500,
					get_pixel_img(&gen->anim[index], j, i));
			}
			j++;
		}
		i++;
	}
}

void	print_anim(t_general *gen)
{
	static int	i = 6;

	make_wheel(gen, i);
	if (gen->key->l == 1 && i < 12)
		i++;
	else if (gen->key->r == 1 && i > 0)
		i--;
	else if (gen->player->an > gen->player->old_an)
	{
		if (i > 0)
			i--;
	}
	else if (gen->player->an < gen->player->old_an)
	{
		if (i < 12)
			i++;
	}
	else if (i > 6)
		i--;
	else if (i < 6)
		i++;
	gen->player->old_an = gen->player->an;
}
