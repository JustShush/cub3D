/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:46 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/27 13:56:04 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_t_img(t_img *img, void *mlx)
{
	if (img)
	{
		mlx_destroy_image(mlx, img->img);
		free(img);
	}
}

int	close_game(t_general *gen)
{
	int	i;

	i = -1;
	while (++i < 13)
		mlx_destroy_image(gen->mlx, gen->anim[i].img);
	free(gen->anim);
	free(gen->textures->f);
	free(gen->textures->c);
	free_t_img(gen->textures->no, gen->mlx);
	free_t_img(gen->textures->so, gen->mlx);
	free_t_img(gen->textures->we, gen->mlx);
	free_t_img(gen->textures->ea, gen->mlx);
	free_array(gen->map->tilemap);
	free_array(gen->file);
	free(gen->textures);
	free(gen->key);
	free(gen->player);
	free(gen->img);
	free(gen->map);
	mlx_destroy_window(gen->mlx, gen->win);
	mlx_destroy_display(gen->mlx);
	free(gen->mlx);
	free(gen);
	exit(0);
}
