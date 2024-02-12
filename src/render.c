/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/09 15:04:03 by mira             ###   ########.fr       */
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
		my_mlx_pixel_put(gen->img, i, draw_start++, get_color(gen->textures->F), gen);
}

void	draw_ceiling(t_general *gen, float draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
		my_mlx_pixel_put(gen->img, i, j++, get_color(gen->textures->C), gen);
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
	if (wall_dist < 0 || draw_start > gen->win_y)
		return ;
	else if(draw_start < 0)
	{
		draw_end = gen->win_y;
		draw_start = 0;
	}
	draw_ceiling(gen, draw_start, i);
//	printf("proj_plane_dis: %f\n", proj_plane_dis);
//    printf("column: %f\n", proj_column_height);
//    printf("draw_start: %f\ndraw_end: %f\n", draw_start, draw_end);
	while (draw_start <= draw_end)
	{
		if (flag == 0)
			my_mlx_pixel_put(gen->img, i, draw_start, RED_PIXEL, gen);
		if (flag == 1)
			my_mlx_pixel_put(gen->img, i, draw_start, ORANGE_PIXEL, gen);
        if(i == gen->win_x/2)
		    my_mlx_pixel_put(gen->img, gen->win_x/2, draw_start, 0xFFFFFF, gen);
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
			draw_wall(gen, hdist, i, 0);
		else
			draw_wall(gen, vdist, i, 1);
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