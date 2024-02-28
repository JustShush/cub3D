/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 12:25:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_player(t_general *gen, float y, float x)
{
	if (check_collision(gen, y, x) == 0)
	{
		gen->player->y = y;
		gen->player->x = x;
	}
}

//Raycast loop. For each ray:
//	- Find wall intersection point
//	- Find distance between player and wall intersection point
//	- Draw line on screen.
int	raycast(t_general *gen, t_ray *ray)
{
	int			i;
	float		hdist;
	float		vdist;
	float		column;

	i = 0;
	column = (float)gen->pov / gen->win_x;
	ray->an = norm(gen->player->an + (gen->pov / 2));
	while (i < gen->win_x)
	{
		horizontal_intersection(gen, gen->ray);
		hdist = dist(gen, ray, ray->hy, ray->hx);
		vertical_intersection(gen, gen->ray);
		vdist = dist(gen, ray, ray->vy, ray->vx);
		if (hdist <= vdist)
			draw(gen, hdist, i, 0);
		else if (hdist > vdist)
			draw(gen, vdist, i, 1);
		ray->an = norm(ray->an - column);
		i++;
	}
	return (0);
}

void	print_display(t_general *gen)
{
	init_img(gen);
	raycast(gen, gen->ray);
	minimap(gen);
	raycast2d(gen);
	print_anim(gen);
	mlx_clear_window(gen->mlx, gen->win);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->img->img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->img->img);
}

int	render(t_general *gen)
{
	if (gen->key->l == 1)
		gen->player->an = norm(gen->player->an - RSPD);
	if (gen->key->r == 1)
		gen->player->an = norm(gen->player->an + RSPD);
	if (gen->key->w == 1)
		move_player(gen, gen->player->y - sin(to_rad(gen->player->an)) * SPD,
			gen->player->x + cos(to_rad(gen->player->an)) * SPD);
	if (gen->key->s == 1)
		move_player(gen,
			gen->player->y - sin(to_rad(norm(gen->player->an + 180))) * SPD,
			gen->player->x
			+ cos(to_rad(norm(gen->player->an + 180))) * SPD);
	if (gen->key->a == 1)
		move_player(gen,
			gen->player->y - sin(to_rad(norm(gen->player->an + 90))) * SPD,
			gen->player->x + cos(to_rad(norm(gen->player->an + 90))) * SPD);
	if (gen->key->d == 1)
		move_player(gen,
			gen->player->y - sin(to_rad(norm(gen->player->an - 90))) * SPD,
			gen->player->x + cos(to_rad(norm(gen->player->an - 90))) * SPD);
	print_display(gen);
	return (0);
}
