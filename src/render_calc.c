/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:34:45 by mira              #+#    #+#             */
/*   Updated: 2024/02/12 12:18:11 by ddiniz-m         ###   ########.fr       */
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

	dx = cos(toRad(ray->an)) * (x - gen->player->x);
	dy = sin(toRad(ray->an)) * (y - gen->player->y);
	dist = (dx - dy);
	beta = norm(gen->player->an - ray->an);
	fix = (dist * cos(toRad(beta)));
	return (fix);
}

//Flag = 0 if horizontal
//Flag = 1 if vertical
void	intersection_iter(t_general *gen, t_ray *ray, float y, float x, int flag)
{
	if (flag == 0)
	{
		while (!point_check(gen, ray->hy, ray->hx))
		{
			ray->hy += y;
			ray->hx += x;
		}
	}
	if (flag == 1)
	{
		while (!point_check(gen, ray->vy, ray->vx))
		{
			ray->vy += y;
			ray->vx += x;
		}
	}
}

//Check intersection of ray and horizontal lines
void	horizontal_intersection(t_general *gen, t_ray *ray)
{
	if (sin(toRad(ray->an)) > 0.0001) //If ray is facing up
	{	
		ray->hy = (((int)gen->player->y >> 6) << 6) - 0.0001;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		intersection_iter(gen, ray, (-64.0), 64.0 / ft_tan(ray->an), 0);
	}
	else if (sin(toRad(ray->an)) < -0.0001)//If ray is facing down
	{
		ray->hy = (((int)gen->player->y >> 6) << 6) + 64.0;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		intersection_iter(gen, ray, 64.0, (-64.0) / ft_tan(ray->an), 0);
	}
	else
	{
		ray->hx = gen->player->x;
		ray->hy = gen->player->y;
		return ;
	}
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_general *gen, t_ray *ray)
{
	if (cos(toRad(ray->an)) > 0.0001) //If ray is facing left
	{
		ray->vx = (((int)gen->player->x >> 6) << 6) + 64.0;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		intersection_iter(gen, ray, (-64.0) * ft_tan(ray->an), 64.0, 1);
	}
	else if ((cos(toRad(ray->an)) < -0.0001)) //If ray is facing right
	{
		ray->vx = (((int)gen->player->x >> 6) << 6) - 0.0001;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		intersection_iter(gen, ray, 64.0 * ft_tan(ray->an), (-64.0), 1);
	}
	else
	{
		ray->vx = gen->player->x;
		ray->vy = gen->player->y;
		return ;
	}
}
