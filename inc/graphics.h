/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:05:21 by ldiogo            #+#    #+#             */
/*   Updated: 2024/02/26 13:26:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <ctype.h>
# include <string.h>
# include "../mlx_linux/mlx.h"
# include "../gnl/gnl.h"
# include <time.h>

# define SCALE 20

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_img;

typedef struct RGB
{
	int	r;
	int	g;
	int	b;
}				t_RGB;

typedef struct textures
{
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
	t_RGB	*c;
	t_RGB	*f;
}				t_textures;

int		readmap(char **map, char *file);
int		numberoflines(char *file);
char	**map_init(char *file);
int		flood_fill(char **map, int x, int y);
int		check_map_closed(char **map);
int		get_start_map(char **map);
int		check_char(char **map);
char	*ft_chrtrim(char *line, char c);
int		get_y(char *file);
int	check_suffix(char *file_path, char *suf);

#endif //BUC3D_BUC3D_H
