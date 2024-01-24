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

typedef struct	s_map
{
	char	**tilemap;
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	int		y;
	int		x;
}				t_map;

typedef struct	s_player
{
	int	x;
	int	y;
}				t_player;

typedef struct	s_ray
{
	int	wall_dist;
	int	dir;
}				t_ray;

typedef struct	s_game
{
	int			pov;
	void		*win;
	void		*mlx;
	int			win_y;
	int			win_x;
	t_ray		*ray;
	t_map		*map;
	t_player	*player;
}				t_game;

//arr_utils.c
void	arr_print(char *str, char **arr);

//check.c
int		check_suffix(char *str);
int		map_check(t_map *map, char **av);

//close.c
int		close_game(t_game *game);

//input.c
int		esc_key(int key, t_game *game);

//map.c
int		map_init(t_map *map, char *map_path);

//str_utils.c
int		first_str(char *s1, char *s2);

#endif