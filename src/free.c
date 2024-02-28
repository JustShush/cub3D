/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/28 14:48:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_t_img(t_img *img, void *mlx)
{
	if (img)
	{
		mlx_destroy_image(mlx, img->img);
		free(img);
	}
}

void	support_free(t_general *gen)
{
	free_array(gen->map->tilemap);
	free_array(gen->file);
	free(gen->key);
	free(gen->player);
	free(gen->img);
	free(gen->textures);
	free(gen->map);
}

void	*error_free(t_general *gen)
{
	free(gen->textures->f);
	free(gen->textures->c);
	free(gen->textures);
	free(gen->key);
	free(gen->player);
	free(gen->img);
	free(gen->map);
	free(gen);
	return (NULL);
}

void	exit_free_check(t_general *gen, char *error)
{
	int	i;

	i = -1;
	if (error)
		printf("%s\n", error);
	while (++i < 13)
		mlx_destroy_image(gen->mlx, gen->anim[i].img);
	free(gen->anim);
	free(gen->textures->f);
	free(gen->textures->c);
	free_t_img(gen->textures->no, gen->mlx);
	free_t_img(gen->textures->so, gen->mlx);
	free_t_img(gen->textures->we, gen->mlx);
	free_t_img(gen->textures->ea, gen->mlx);
	mlx_destroy_display(gen->mlx);
	support_free(gen);
	free(gen->mlx);
	free(gen);
	exit(0);
}
