/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/08 11:55:46 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	ft_tan(float angle)
{
	float	s;
	float	c;

	s = sin(toRad(angle));
	c = cos(toRad(angle));
	if (c != 0)
		return (s / c);
	return (s);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//Checks if point is inside the screen
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 && y <= gen->win_y && x <= gen->win_x
		&& y / 64 < gen->map->y 
		&& x / 64 < ft_strlen(gen->map->tilemap[y / 64])
		&& gen->map->tilemap[y / 64][x / 64] != '1')
		return (0);
	return (1);
}

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

void	draw_floor(t_general *gen, float draw_start, int i)
{
	while (draw_start < gen->win_y)
	{
//		if (draw_start >= gen->win_y - 100 && draw_start < gen->win_y && i >= 0 && i <= 120)
//		{
//			draw_start++;
//			continue ;
//		}
		my_mlx_pixel_put(gen->img, i, draw_start++, GREEN_PIXEL);
	}
}

void	draw_ceiling(t_general *gen, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
	{
		my_mlx_pixel_put(gen->img, i, j++, BLUE_PIXEL);
	}
}

void	draw_wall(t_general *gen, float wall_dist, int i, int flag)
{
	float	draw_end;
	float	draw_start;
	float	proj_plane_dis;
	float	proj_column_height;

	proj_plane_dis = (gen->win_x / 2) / ft_tan(gen->pov);
	proj_column_height = ((64 / wall_dist) * proj_plane_dis);
	draw_start = (gen->win_y / 2) - (proj_column_height / 2);
	draw_end = (gen->win_y / 2) + (proj_column_height / 2);
	if (wall_dist < 0 || draw_start < 0 || draw_start > gen->win_y)
		return ;
	draw_ceiling(gen, draw_start, i);
	while (draw_start <= draw_end)
	{
//		if (draw_start >= gen->win_y - 100 && draw_start < gen->win_y && i >= 0 && i <= 120)
//		{
//			draw_start++;
//			continue ;
//		}
		if (flag == 0)
			my_mlx_pixel_put(gen->img, i, draw_start, RED_PIXEL);
		if (flag == 1)
			my_mlx_pixel_put(gen->img, i, draw_start, ORANGE_PIXEL);
		draw_start++;
	}
	draw_floor(gen, draw_start, i);
}


//Check intersection of ray and horizontal lines
void	horizontal_intersection(t_general *gen, t_ray *ray)
{
	int	by;
	int	bx;

	by = 0;
	bx = 0;
	if (sin(toRad(ray->an)) > 0.001) //If ray is facing up
	{	
		ray->hy = (((int)gen->player->y >> 6) << 6) - 0.001;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		by = -64;
		bx = 64 / ft_tan(ray->an);
	}
	else if (sin(toRad(ray->an)) < -0.001)//If ray is facing down
	{
		ray->hy = (((int)gen->player->y >> 6) << 6) + 64;
		ray->hx = gen->player->x + (gen->player->y - ray->hy) / ft_tan(ray->an);
		by = 64;
		bx = -64 / ft_tan(ray->an);
	}
	else
	{
		ray->hx = gen->player->x;
		ray->hy = gen->player->y;
		return ;
	}
	while (!point_check(gen, ray->hy, ray->hx))
	{
		ray->hx += bx;
		ray->hy += by;
	}
	// printf("ray->hy: %f\nray->hx: %f\n",ray->hy, ray->hx);
}

//Check intersection of ray and vertical lines
void	vertical_intersection(t_general *gen, t_ray *ray)
{
	int	by;
	int	bx;

	by = 0;
	bx = 0;
	if (cos(toRad(ray->an)) > 0.001) //If ray is facing left
	{
		ray->vx = (((int)gen->player->x >> 6) << 6) + 64;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		bx = 64;
		by = (-64) / ft_tan(ray->an);
	}
	else if ((cos(toRad(ray->an)) < -0.001)) //If ray is facing right
	{
		ray->vx = (((int)gen->player->x >> 6) << 6) - 0.001;
		ray->vy = gen->player->y + (gen->player->x - ray->vx) * ft_tan(ray->an);
		bx = -64;
		by = 64 / ft_tan(ray->an);
	}
	else
	{
		ray->vx = gen->player->x;
		ray->vy = gen->player->y;
		return ;
	}
	while (!point_check(gen, ray->vy, ray->vx))
	{
		ray->vx += bx;
		ray->vy += by;
	}
	// printf("ray->vy: %f\nray->vx: %f\n",ray->vy, ray->vx);
}

//Raycast loop. For each ray:
//	- Find wall intersection point
//	- Find distance between player and wall intersection point
//	- Draw line on screen.
int	raycast(t_general *gen, t_ray *ray)
{
	int			i;
	double		hdist;
	double		vdist;
	float		column;

	i = 0;
	column = (float)gen->pov/gen->win_x;
	ray->an = norm(gen->player->an + (gen->pov / 2));
	while (i < gen->win_x)
	{
		horizontal_intersection(gen, gen->ray);
		hdist = dist(gen, ray, ray->hy, ray->hx);
		vertical_intersection(gen, gen->ray);
		vdist = dist(gen, ray, ray->vy, ray->vx);
		if (hdist <= vdist)
		{
			draw_wall(gen, hdist, i, 0);
			/* mlx_pixel_put(gen->mlx, gen->win, ray->hx, ray->hy, 0xFFFFFF); */
		}
		else
		{
			draw_wall(gen, vdist, i, 1);
			/* mlx_pixel_put(gen->mlx, gen->win, ray->vx, ray->vy, 0xFFFFFF); */
		}
		ray->an = norm(ray->an - column);
		i++;
	}
	return (0);
}

void	init_img(t_general *gen)
{
	gen->img->img = mlx_new_image(gen->mlx, gen->win_x, gen->win_y);
	gen->img->addr = mlx_get_data_addr(gen->img->img, &gen->img->bits_per_pixel, &gen->img->line_length, &gen->img->endian);
}

void	print_display(t_general *gen)
{
	init_img(gen);
	raycast(gen, gen->ray);
	minimap(gen);
	draw_player(gen);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->img->img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->img->img);
}

//Raycast based on player's direction and pov
int	render(t_general *gen)
{
	if (gen->key->l == 1)
		gen->player->an = norm(gen->player->an + 1);
	if (gen->key->r == 1)
		gen->player->an = norm(gen->player->an - 1);
	if (gen->key->w == 1)//W
	{
		gen->player->y -= sin(toRad(gen->player->an));
		gen->player->x -= cos(toRad(gen->player->an));
	}
	if (gen->key->s == 1)
	{
		gen->player->y += sin(toRad(gen->player->an));
		gen->player->x += cos(toRad(gen->player->an));
	}
	if (gen->key->a == 1)
	{
		gen->player->y -= sin(toRad(norm(gen->player->an - 90)));
		gen->player->x -= cos(toRad(norm(gen->player->an - 90)));
	}
	if (gen->key->d == 1)
	{
		gen->player->y -= sin(toRad(norm(gen->player->an + 90)));
		gen->player->x -= cos(toRad(norm(gen->player->an + 90)));
	}
	print_display(gen);
	return(0);
}