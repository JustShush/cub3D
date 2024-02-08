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

# define	PI			3.14159265358979323846
# define	RED_PIXEL		0xFF0000
# define	ORANGE_PIXEL	0xFF8000
# define	GREEN_PIXEL		0x00FF00
# define	BLUE_PIXEL		0x0000FF

typedef struct	s_map
{
	char	**tilemap;
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	int		y;
}				t_map;

typedef struct	s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}				t_key;

typedef struct	s_player
{
	float		x;
	float		y;
	float		an;
}				t_player;

typedef struct	s_ray
{
	float		hx;
	float		hy;
	float		vy;
	float		vx;
	float		an;
	float		wall_dist;
}				t_ray;

typedef struct	s_general
{
	int			pov;
	void		*win;
	void		*mlx;
	int			win_y;
	int			win_x;
	char		**file;
	int			map_start;
	int 		map_width;
	int 		map_height;
	t_data		*img;
	t_key		*key;
	t_ray		*ray;
	t_map		*map;
	t_player	*player;
	t_textures	*textures;
}				t_general;

//map
void		save_img(t_general *gen, char *dir, char *line, int j);
int			check_color(char *line);
void		save_color(t_general *gen, char dir, char *line, int j);
int			get_textures(t_general *gen);
int			check_textures(t_general *gen);
int			check_valid_color(t_general *gen);
int			check_map(t_general *gen);
void		tilemap(t_map *map, char *map_path);

//close.c
int			close_game(t_general *gen);

//input.c
int			key_release(int key, t_general *gen);
int			key_press(int key, t_general *gen);

//init.c
void		player_pos(t_general *gen, char **map);
t_general	*init(t_general *gen, char **av);

//render.c
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			render(t_general *gen);
int			point_check(t_general *gen, int y, int x);

//minimap.c
void		put_player(t_general *gen, int py, int px, int r);
void		put_rays(t_general *gen, int angle, int py, int px, int len);
int			minimap(t_general *gen);
void		put_square(t_general *gen, int y, int x, int color);
int 		sizeofmap_x(t_general *gen);
int			sizeofmap_y(t_general *gen);

//render_utils.c
double		norm(double angle);
float		toRad(float d);
int			sign(int an, int flag);
int			first_str(char *s1, char *s2);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif