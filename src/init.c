/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:05 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/09 13:17:04 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_img(t_general *gen)
{
	gen->img->img = mlx_new_image(gen->mlx, gen->win_x, gen->win_y);
	gen->img->addr = mlx_get_data_addr(gen->img->img, &gen->img->bits_per_pixel, &gen->img->line_length, &gen->img->endian);
}

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

void	init_anim(t_general *gen)
{
	int i;
	int x;
	int y;
	char *dir;
	char *tmp;

	i = 1;
	while(i <= 13)
	{
		dir = ft_strdup("textures/anim/steering-wheel-");
		tmp = ft_itoa(i);
		dir = ft_strjoin(dir, tmp);
		dir = ft_strjoin(dir, ".xpm");
		gen->anim->data->img = mlx_xpm_file_to_image(gen->mlx, dir, &x, &y);
		free(dir);
		free(tmp);
		i++;
	}
	gen->anim->frame = 0;
	gen->anim->frame_count = 0;
}

t_general	*init(t_general *gen, char **av)
{
	t_ray ray;
	gen = (t_general *)malloc(sizeof(t_general));
	gen->textures = (t_textures *)malloc(sizeof(t_textures));
	gen->textures->C = (t_RGB *)malloc(sizeof(t_RGB));
	gen->textures->F = (t_RGB *)malloc(sizeof(t_RGB));
	gen->map = (t_map *)malloc(sizeof(t_map));
	gen->key = (t_key *)malloc(sizeof(t_key));
	gen->player = (t_player *)malloc(sizeof(t_player));
	gen->img = (t_data *)malloc(sizeof(t_data));
	gen->anim = (t_anim *)malloc(sizeof(t_anim));
	gen->ray = &ray;
	gen->file = map_init(av[1]);
	tilemap(gen->map, av[1]);
	gen->key->w = 0;
	gen->key->d = 0;
	gen->key->s = 0;
	gen->key->a = 0;
	gen->key->l = 0;
	gen->key->r = 0;
	gen->pov = 60;
	gen->win_x = 1280;
	gen->win_y = 800;
	gen->ray->an = 0;
	return (gen);
}