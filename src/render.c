/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:37:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/20 15:28:50 by ddiniz-m         ###   ########.fr       */
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
	if (y >= 0 && x >= 0 &&  y / CUB < gen->map->y
		&& x / CUB < ft_strlen(gen->map->tilemap[y / CUB])
		&& gen->map->tilemap[y / CUB][x / CUB] != '1')
		return (0);
	return (1);
}

void	draw_floor(t_general *gen, int draw_start, int i)
{
	while (draw_start < gen->win_y)
		my_mlx_pixel_put(gen, gen->img, i, draw_start++, get_color(gen->textures->F));
}

void	draw_ceiling(t_general *gen, int draw_start, int i)
{
	int	j;

	j = 0;
	while (j < draw_start)
		my_mlx_pixel_put(gen, gen->img, i, j++, get_color(gen->textures->C));
}

unsigned int get_pixel_color(t_img *img, int pixelx, int pixely)
{
	unsigned int		color;

	if (pixelx >= 0 && pixelx < img->width && pixely >= 0 && pixely < img->height)
		color = *(unsigned int *)(img->addr + (pixely * img->line_length) +
			(pixelx * img->bits_per_pixel / 4));
	else
		color = 0;
	return (color);
}

void	draw_walls(t_general *gen, int x, int draw_start, int line_h, int flag)
{
	int				pixely;
	int				pixelx;
	unsigned int	color;

	pixely = (draw_start - gen->win_y / 2 + line_h / 2) * 64 / line_h;
	if (flag == 0)
	{
		pixelx = (int)gen->ray->hx % 32;
		if (sin(toRad(gen->ray->an)) > 0.0001)
			color = get_pixel_color(gen->textures->NO, pixelx, pixely);
		else if (sin(toRad(gen->ray->an)) < -0.0001)
			color = get_pixel_color(gen->textures->SO, pixelx, pixely);
	}
	if (flag == 1)
	{
		pixelx = (int)gen->ray->vy % 32;
		if (cos(toRad(gen->ray->an)) > 0.0001)
			color = get_pixel_color(gen->textures->EA, pixelx, pixely);
		else if (cos(toRad(gen->ray->an)) < -0.0001)
			color = get_pixel_color(gen->textures->WE, pixelx, pixely);
	}
	my_mlx_pixel_put(gen, gen->img, x, draw_start, color);
}

void	draw(t_general *gen, float wall_dist, int i, int flag)
{
	int	draw_end;
	int	draw_start;
	int	proj_plane_dis;
	int	line_h;
	
	proj_plane_dis = (gen->win_x / 2) / ft_tan(gen->pov);
	line_h = ((CUB / wall_dist) * proj_plane_dis);
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
	while (draw_start < draw_end)
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
	if (y >= 0 && x >= 0 &&  y / CUB < gen->map->y
		&& x / CUB < ft_strlen(gen->map->tilemap[y / CUB])
		&& gen->map->tilemap[y / CUB][x / CUB] != '1')
		return (0);
	return (1);
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
	return (color);
}

void	make_wheel(t_general *gen, int index)
{
	int i;
	int j;

	i = 0;
	while(i < 500)
	{
		j = 0;
		while (j < 640)
		{
			if((int)get_pixel_img(&gen->anim[index], j, i) != -16777216 && (int)get_pixel_img(&gen->anim[index], j, i) != 0)
			{
				my_mlx_pixel_put(gen, gen->img, j + gen->win_x / 2 - 320, i + gen->win_y - 500, get_pixel_img(&gen->anim[index], j, i));
			}
			j++;
		}
		i++;
	}
}

void	print_anim(t_general *gen)
{
	static int i = 6;

	make_wheel(gen, i);
//	printf("old_an: %f\n", gen->player->old_an);
//	printf("an: %f\n", gen->player->an);
	if(gen->key->l == 1)
	{
		if(i < 12)
			i++;
	}
	else if(gen->key->r == 1)
	{
		if(i > 0)
			i--;
	}
	else if(gen->player->an > gen->player->old_an)
	{
		if(i > 0)
			i--;
	}
	else if(gen->player->an < gen->player->old_an)
	{
		if(i < 12)
			i++;
	}
	else
	{
		if(i < 6)
			i++;
		else if(i > 6)
			i--;
	}
	gen->player->old_an = gen->player->an;
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
//	display_position(gen);
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

//Raycast based on player's direction and gen->pov
int	render(t_general *gen)
{
	if (gen->key->l == 1)
		gen->player->an = norm(gen->player->an - RSPD);
	if (gen->key->r == 1)
		gen->player->an = norm(gen->player->an + RSPD);
	if (gen->key->w == 1)//W
	{
		move_player(gen, gen->player->y - sin(toRad(gen->player->an)) * SPD, gen->player->x + cos(toRad(gen->player->an)) * SPD);
	}
	if (gen->key->s == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an + 180))) * SPD, gen->player->x + cos(toRad(norm(gen->player->an + 180))) * SPD);
	}
	if (gen->key->a == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an + 90))) * SPD, gen->player->x + cos(toRad(norm(gen->player->an + 90))) * SPD);
	}
	if (gen->key->d == 1)
	{
		move_player(gen, gen->player->y - sin(toRad(norm(gen->player->an - 90))) * SPD, gen->player->x + cos(toRad(norm(gen->player->an - 90))) * SPD);
	}
	print_display(gen);
	return(0);
} 