/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:05:13 by ldiogo            #+#    #+#             */
/*   Updated: 2024/02/26 11:59:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/src/libft.h"
# include "../gnl/gnl.h"
# include "graphics.h"

# define X_SENSE			2
# define SPD				5
# define RSPD				3
# define CUB				64
# define RED_PIXEL		0xFF0000
# define ORANGE_PIXEL	0xFF8000
# define GREEN_PIXEL		0x00FF00
# define BLUE_PIXEL		0x0000FF
# define PI				3.14159265358979323846

typedef struct s_map
{
	char	**tilemap;
	int		y;
}				t_map;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}				t_key;

typedef struct s_player
{
	float		x;
	float		y;
	float		an;
	float		old_an;
}				t_player;

typedef struct s_ray
{
	float		hx;
	float		hy;
	float		vy;
	float		vx;
	float		an;
	float		wall_dist;
}				t_ray;

typedef struct s_su
{
	int	draw_end;
	int	draw_start;
	int	proj_plane_dis;
	int	line_h;
}				t_su;

typedef struct s_general
{
	int			pov;
	void		*win;
	void		*mlx;
	int			win_x;
	int			win_y;
	char		**file;
	t_img		*anim;
	t_img		*img;
	t_key		*key;
	t_ray		*ray;
	t_map		*map;
	t_player	*player;
	t_textures	*textures;
}				t_general;

//---------------------------------------map/----------------------------------
// check.c
int				check_color(char *line, char **color);
int				check_map(t_general *gen);

// map_utils2.c
void			save_color(t_general *gen, char dir, char *line, int j);
int				check_valid_color(t_general *gen);

// map.c
int				tilemap(t_map *map, char *map_path);

//-----------------------------------------------------------------------------
// close.c
int				close_game(t_general *gen);

// input.c
int				key_release(int key, t_general *gen);
int				key_press(int key, t_general *gen);

// init.c
void			init_img(t_general *gen);
void			player_pos(t_general *gen, char **map);
t_general		*init(t_general *gen, char **av);

// minimap_put.c
void			put_map(t_general *gen, int *num);
void			put_player(t_general *gen, int py, int px, int r);
void			put_rays(t_general *gen, int angle, int py, int px);

// render_anim.c
void			print_anim(t_general *gen);

// render_calc.c
float			dist(t_general *gen, t_ray *ray, float y, float x);
void			horizontal_intersection(t_general *gen, t_ray *ray);
void			vertical_intersection(t_general *gen, t_ray *ray);

// render_draw.c
void			draw(t_general *gen, float wall_dist, int i, int flag);

// render_utils.c
void			my_mlx_pixel_put(t_general *gen, int x, int y, unsigned int color);
double			norm(double angle);
float			to_rad(float d);
float			ft_tan(float angle);

// render_utils2.c
unsigned int	get_pixel_img(t_img *img, int x, int y);
int				get_color(t_RGB *color);
unsigned int	get_pixel_color(t_img *img, float pixelx, float pixely);
int				check_collision(t_general *gen, int y, int x);

// render.c
int				render(t_general *gen);
int				point_check(t_general *gen, int y, int x);

// minimap.c
void			raycast2d(t_general *gen);
int				minimap(t_general *gen);
void			put_square(t_general *gen, int y, int x, int color);

//textures.c
int				check_textures(t_general *gen);
int				get_textures(t_general *gen);
void			save_img(t_general *gen, char *dir, char *line, int j);


// utils.c
int				first_str(char *s1, char *s2);
int				line_empty(char *line);
void			free_array(char **array);
void			*error_free(t_general *gen);
void			exit_free_check(t_general *gen);
void			free_t_img(t_img *img, void *mlx);
void			make_null(t_general *gen, char dir);
void			make_img_null(t_general *gen, char *dir);

#endif