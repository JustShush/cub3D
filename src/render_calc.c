/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:34:45 by mira              #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Takes ray x and y and and returns their distance to the player
float	dist(t_general *gen, t_ray *ray, float y, float x)
{
	float	dx;
	float	dy;
	float	fix;
	float	beta;
	float	dist;

	dx = cos(to_rad(ray->an)) * (x - gen->player->x);
	dy = sin(to_rad(ray->an)) * (y - gen->player->y);
	dist = (dx - dy);
	beta = norm(gen->player->an - ray->an);
	fix = (dist * cos(to_rad(beta)));
	return (fix);
}

//Flag = 0 if horizontal
//Flag = 1 if vertical
void	intersection_iter(t_general *gen, float y, float x, int flag)
{
	if (flag == 0)
	{
		while (!point_check(gen, gen->ray->hy, gen->ray->hx))
		{
			gen->ray->hy += y;
			gen->ray->hx += x;
		}
	}
	if (flag == 1)
	{
		while (!point_check(gen, gen->ray->vy, gen->ray->vx))
		{
			gen->ray->vy += y;
			gen->ray->vx += x;
		}
	}
}

//Check intersection of ray and horizontal lines
//If ray is facing up
//If ray is facing down
void	horizontal_intersection(t_general *gen, t_ray *ray)
{
	int	log2;

	log2 = log(CUB) / log(2);
	if (sin(to_rad(ray->an)) > -1.0E-8 && sin(to_rad(ray->an)) < 1.0E-8)
	{
		ray->hy = gen->player->y;
		ray->hx = gen->player->x;
		if (cos(to_rad(ray->an)) > 0.001)
			intersection_iter(gen, 0, CUB, 0);
		if (cos(to_rad(ray->an)) < -0.001)
			intersection_iter(gen, 0, -CUB, 0);
	}
	else if (sin(to_rad(ray->an)) > 1.0E-8)
	{
		ray->hy = (((int)gen->player->y >> log2) << log2) - 0.0001;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		intersection_iter(gen, (-CUB), CUB / ft_tan(ray->an), 0);
	}
	else if (sin(to_rad(ray->an)) < -1.0E-8)
	{
		ray->hy = (((int)gen->player->y >> log2) << log2) + CUB;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		intersection_iter(gen, CUB, (-CUB) / ft_tan(ray->an), 0);
	}
}

//Check intersection of ray and vertical lines
//If ray is facing left
//If ray is facing right
void	vertical_intersection(t_general *gen, t_ray *ray)
{
	int	log2;

	log2 = log(CUB) / log(2);
	if (cos(to_rad(ray->an)) < 1.0E-8 && (cos(to_rad(ray->an)) > -1.0E-8))
	{
		ray->vx = gen->player->x;
		ray->vy = gen->player->y;
		intersection_iter(gen, (-CUB), 0, 1);
	}
	else if (cos(to_rad(ray->an)) > 1.0E-8)
	{
		ray->vx = (((int)gen->player->x >> log2) << log2) + CUB;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		intersection_iter(gen, (-CUB) * ft_tan(ray->an), CUB, 1);
	}
	else if ((cos(to_rad(ray->an)) < -1.0E-8))
	{
		ray->vx = (((int)gen->player->x >> log2) << log2) - 0.0001;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		intersection_iter(gen, CUB * ft_tan(ray->an), (-CUB), 1);
	}
}
