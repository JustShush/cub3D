/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/13 18:18:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int get_color(t_RGB *color)
{
	return (color->r << 16 | color->g << 8 | color->b);
}

//Checks if point is inside the screen
//Returns 1 if wall or invalid
int	point_check(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 &&  y / 64 < gen->map->y
		&& x / 64 < ft_strlen(gen->map->tilemap[y / 64])
		&& gen->map->tilemap[y / 64][x / 64] != '1')
		return (0);
	return (1);
}

void	draw_floor(t_general *gen, float draw_start, int i)
{
	while (draw_start < gen->win_y)
		my_mlx_pixel_put(gen, gen->img, i, draw_start++, get_color(gen->textures->F));
}

void	draw_ceiling(t_general *gen, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
		my_mlx_pixel_put(gen, gen->img, i, j++, get_color(gen->textures->C));
}

void	draw_walls(t_general *gen, int x, int y, int h, int flag)
{
	unsigned int	color;

	if (flag == 0)
		{
			if (sin(toRad(gen->ray->an)) > 0.0001)
				color = get_pixel_color(gen->textures->NO, gen->ray->hx, gen->ray->hy, h, flag, y);
			else
				color = get_pixel_color(gen->textures->SO, gen->ray->hx, gen->ray->hy, h, flag, y);
		}
		if (flag == 1)
		{
			if (cos(toRad(gen->ray->an)) > 0.0001)
				color = get_pixel_color(gen->textures->EA, gen->ray->vx, gen->ray->vy, h, flag, y);
			else
				color = get_pixel_color(gen->textures->WE, gen->ray->vx, gen->ray->vy, h, flag, y);
		}
		my_mlx_pixel_put(gen, gen->img, x, y, color);
		if (x == gen->win_x / 2)
			my_mlx_pixel_put(gen, gen->img, gen->win_x / 2, y, 0xFFFFFF);
}

void	draw(t_general *gen, float wall_dist, int i, int flag)
{
	float	draw_end;
	float	draw_start;
	float	proj_plane_dis;
	float	line_h;
	
	proj_plane_dis = (gen->win_x / 2) / ft_tan(gen->pov);
	line_h = ((64 / wall_dist) * proj_plane_dis);
	draw_start = (gen->win_y / 2) - (line_h / 2);
	draw_end = (gen->win_y / 2) + (line_h / 2);
	if (wall_dist < 0 || draw_start > gen->win_y)
		return ;
	else if(draw_start < 0)
	{
		draw_end = gen->win_y;
		draw_start = 0;
	}
	draw_ceiling(gen, draw_start, i);
	while (draw_start <= draw_end)
	{
		draw_walls(gen, i, draw_start, line_h, flag);
		draw_start++;
	}
	draw_floor(gen, draw_start, i);
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
			draw(gen, hdist, i, 0);
		else
			draw(gen, vdist, i, 1);
		ray->an = norm(ray->an - column);
		i++;
	}
	return (0);
}

void	display_position(t_general *gen)
{
	char *x;
	char *y;

	x = ft_itoa(gen->player->x);
	y = ft_itoa(gen->player->y);
	mlx_string_put(gen->mlx, gen->win, 10, 20, 0xFFFFFF, "Player position:");
	mlx_string_put(gen->mlx, gen->win, 10, 40, 0xFFFFFF, x);
	mlx_string_put(gen->mlx, gen->win, 10, 60, 0xFFFFFF, y);
	free(x);
	free(y);
}

int check_collision(t_general *gen, int y, int x)
{
	if (y >= 0 && x >= 0 &&  y / 64 < gen->map->y
		&& x / 64 < ft_strlen(gen->map->tilemap[y / 64])
		&& gen->map->tilemap[y / 64][x / 64] != '1')
		return (0);
	return (1);
}

void	print_display(t_general *gen)
{
	init_img(gen);
	raycast(gen, gen->ray);
	minimap(gen);
	raycast2d(gen);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->img->img, 0, 0);
	display_position(gen);
	mlx_destroy_image(gen->mlx, gen->img->img);
}

void	move_player(t_general *gen, float y, float x)
{
	if (check_collision(gen, y, x) == 0)
	{
		gen->player->y = y;
		gen->player->x = x;
	}
}

//Raycast based on player's direction and pov
int	render(t_general *gen)
{
	if (gen->key->l == 1)
		gen->player->an = norm(gen->player->an - 2);
	if (gen->key->r == 1)
		gen->player->an = norm(gen->player->an + 2);
	if (gen->key->w == 1)//W
	{
		move_player(gen, gen->player->y - sin(toRad(gen->player->an)) * 2, gen->player->x + cos(toRad(gen->player->an)) * 2);
	}
	if (gen->key->s == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an + 180))) * 2, gen->player->x + cos(toRad(norm(gen->player->an + 180))) * 2);
	}
	if (gen->key->a == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an + 90))) * 2, gen->player->x + cos(toRad(norm(gen->player->an + 90))) * 2);
	}
	if (gen->key->d == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an - 90))) * 2, gen->player->x + cos(toRad(norm(gen->player->an - 90))) * 2);
	}
	print_display(gen);
	return(0);
} 