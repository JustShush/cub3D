#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
# include "../mlx_linux/mlx.h"
# include "../libft/src/libft.h"

typedef struct	s_game
{
	void	*win;
	void	*mlx;
}				t_game;

//check.c
int	check_suffix(char *str);
int	map_check(char **av);

//close.c
int	close_game(t_game *game);

//input.c
int	esc_key(int key, t_game *game);

//map.c

#endif