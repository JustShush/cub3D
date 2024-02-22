/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:16:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:36:22 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Casts rays for minimap and puts player
void	raycast2d(t_general *gen)
{
	int	i;
	int	x;
	int	y;
	int	pradius;

	pradius = 2;
	i = gen->player->an;
	x = gen->player->x * SCALE / CUB;
	y = (gen->player->y * SCALE / CUB);
	if (i >= gen->player->an - (gen->pov / 2))
		put_rays(gen, i--, y, x);
	put_player(gen, y, x, pradius);
}

int	minimap(t_general *gen)
{
	int	num[4];

	num[0] = 0;
	num[1] = 0;
	num[2] = 0;
	num[3] = 0;
	raycast2d(gen);
	while (gen->map->tilemap[num[0]])
	{
		while (gen->map->tilemap[num[0]][num[1]]
			&& gen->map->tilemap[num[0]][num[1]] != '\n')
		{
			put_map(gen, num);
			num[2] += SCALE;
			num[1]++;
		}
		num[3] += SCALE;
		num[2] = 0;
		num[1] = 0;
		num[0]++;
	}
	return (0);
}
