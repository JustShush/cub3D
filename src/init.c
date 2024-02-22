/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:05 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:34:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_img(t_general *gen)
{
	gen->img->img = mlx_new_image(gen->mlx,
			gen->win_x, gen->win_y);
	gen->img->addr = mlx_get_data_addr(gen->img->img, &gen->img->bits_per_pixel,
			&gen->img->line_length, &gen->img->endian);
}

void	init_anim(t_general *gen)
{
	char	*path;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 1;
	gen->anim = (t_img *)malloc(sizeof(t_img) * 13);
	while (i <= 13)
	{
		tmp = ft_itoa(i);
		path = ft_strjoin("./textures/anim/steering-wheel-", tmp);
		tmp2 = ft_strjoin(path, ".xpm");
		gen->anim[i - 1].img = mlx_xpm_file_to_image(gen->mlx, tmp2,
				&gen->anim[i - 1].width, &gen->anim[i - 1].height);
		gen->anim[i - 1].addr = mlx_get_data_addr(gen->anim[i - 1].img,
				&(gen->anim[i - 1].bits_per_pixel),
				&(gen->anim[i - 1].line_length), &(gen->anim[i - 1].endian));
		free(path);
		free(tmp);
		free(tmp2);
		i++;
	}
}

void	more_init(t_general *gen)
{
	gen->key->w = 0;
	gen->key->d = 0;
	gen->key->s = 0;
	gen->key->a = 0;
	gen->key->l = 0;
	gen->key->r = 0;
	gen->win_x = 1280;
	gen->win_y = 800;
	gen->pov = 60;
	gen->ray->an = 0;
	gen->player->old_an = 0;
}

t_general	*init(t_general *gen, char **av)
{
	t_ray	ray;

	gen = (t_general *)malloc(sizeof(t_general));
	gen->textures = (t_textures *)malloc(sizeof(t_textures));
	gen->textures->c = (t_RGB *)malloc(sizeof(t_RGB));
	gen->textures->f = (t_RGB *)malloc(sizeof(t_RGB));
	gen->map = (t_map *)malloc(sizeof(t_map));
	gen->key = (t_key *)malloc(sizeof(t_key));
	gen->player = (t_player *)malloc(sizeof(t_player));
	gen->img = (t_img *)malloc(sizeof(t_img));
	gen->ray = &ray;
	gen->file = map_init(av[1]);
	tilemap(gen->map, av[1]);
	gen->mlx = mlx_init();
	init_anim(gen);
	more_init(gen);
	return (gen);
}
