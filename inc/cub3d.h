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

# define	X_SENSE			2
# define	SPD				2
# define	RSPD			2
# define	CUB				64
# define	RED_PIXEL		0xFF0000
# define	ORANGE_PIXEL	0xFF8000
# define	GREEN_PIXEL		0x00FF00
# define	BLUE_PIXEL		0x0000FF
# define	PI				3.14159265358979323846

typedef struct	s_map
{
	char	**tilemap;
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	int		y;
}				t_map;

typedef struct s_anim
{
	t_img	*data;
	int		frame;
	int		frame_count;
}				t_anim;

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

typedef struct	s_mouse
{
	int		x;
	int		y;
}				t_mouse;

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
	int			win_x;
	int			win_y;
	char		**file;
	int			map_start;
	int 		map_width;
	int 		map_height;
	t_anim 		*anim;
	t_img		*img;
	t_key		*key;
	t_ray		*ray;
	t_map		*map;
	t_player	*player;
	t_textures	*textures;
}				t_general;

//map
//map/check.c
int			check_valid_color(t_general *gen);
int			check_map(t_general *gen);
int			check_textures(t_general *gen);
int			get_textures(t_general *gen);
void		save_color(t_general *gen, char dir, char *line, int j);
int			check_color(char *line);
void		save_img(t_general *gen, char *dir, char *line, int j);

//map/map.c
void		tilemap(t_map *map, char *map_path);

//map/map_utils.c
int			sizeofmap_x(t_general *gen);
int			sizeofmap_y(t_general *gen);

//close.c
int			close_game(t_general *gen);

//input.c
int			key_release(int key, t_general *gen);
int			key_press(int key, t_general *gen);

//init.c
void		init_img(t_general *gen);
void		player_pos(t_general *gen, char **map);
t_general	*init(t_general *gen, char **av);
void		make_background(t_general *gen);

//render_calc.c
float		dist(t_general *gen, t_ray *ray, float y, float x);
void		horizontal_intersection(t_general *gen, t_ray *ray);
void		vertical_intersection(t_general *gen, t_ray *ray);

//render_utils.c
void			my_mlx_pixel_put(t_general *gen, t_img *img, int x, int y, int color);
double			norm(double angle);
float			toRad(float d);
float			ft_tan(float angle);

//render.c
int			render(t_general *gen);
int			point_check(t_general *gen, int y, int x);

//minimap.c
void		raycast2d(t_general *gen);
int			minimap(t_general *gen);
void		put_square(t_general *gen, int y, int x, int color);
int 		sizeofmap_x(t_general *gen);
int			sizeofmap_y(t_general *gen);


//utils.c
int			first_str(char *s1, char *s2);
int			line_empty(char *line);

#endif