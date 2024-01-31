//
// Created by ldiogo on 1/24/24.
//

#ifndef BUC3D_BUC3D_H
#define BUC3D_BUC3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "../mlx_linux/mlx.h"
#include "../gnl/gnl.h"

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		width;
	int 		height;
}				t_img;

typedef struct RGB
{
	int	r;
	int	g;
	int	b;
}				t_RGB;

typedef struct textures
{
	t_img	*NO;
	t_img	*SO;
	t_img	*WE;
	t_img	*EA;
	t_RGB	*C;
	t_RGB	*F;
}				t_textures;

void	readmap(char **map, char *file);
int		numberoflines(char *file);
char	**map_init(char *file);
void	printf_array(char **array);
int		flood_fill(char **map, int x, int y);
int		check_map_closed(char **map);
int		line_empty(char *line);
int		get_start_map(char **map);
int		check_char(char **map);
char	*ft_chrtrim(char *line, char c);
int		getY(char *file);

#endif //BUC3D_BUC3D_H
