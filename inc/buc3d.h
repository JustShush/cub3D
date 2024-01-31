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
#include "../get_next_line/get_next_line.h"

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
	int r;
	int g;
	int b;
}				t_RGB;

typedef struct textures
{
    t_img *NO;
    t_img *SO;
    t_img *WE;
    t_img *EA;
    t_RGB *C;
    t_RGB *F;
}				t_textures;

typedef struct general
{
	void *mlx;
	void *win;
	char **map;
	t_textures *textures;
}				t_general;

char	*ft_strdup(const char *s1);
void	readmap(char **map, char *file);
int	numberoflines(char *file);
char    **map_init(char *file);
char	**ft_split(char *str, char c);
char	*get_word(char *str, char c);
int	get_num_words(char *str, char c);
char	**ft_split_quote(char *str, char *quotes, char c);
char	*get_word_quote(char *str, char *quotes, char c, int n);
int	get_num_words_quote(char *str, char *quotes, char c);
void    printf_array(char **array);
char	*ft_strdup(const char *s1);
char *ft_strtrim(char *line, char c);
int ft_atoi(char *str);
int flood_fill(char **map, int x, int y);
int check_map_closed(char **map);
int line_empty(char *line);
int get_start_map(char **map);
int check_char(char **map);
void save_img(t_general *gen, char *dir, char *line, int j);
int check_color(char *line);
void save_color(t_general *gen, char dir, char *line, int j);
int get_textures(t_general *gen);
int check_textures(t_general *gen);
int check_valid_color(t_general *gen);
int check_map(t_general *gen);


#endif //BUC3D_BUC3D_H
