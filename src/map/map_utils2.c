/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:29:36 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/28 14:41:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	assign_color(t_general *gen, char dir, char **color)
{
	if (dir == 'C')
	{
		gen->textures->c = (t_RGB *)malloc(sizeof(t_RGB));
		gen->textures->c->r = ft_atoi(color[0]);
		gen->textures->c->g = ft_atoi(color[1]);
		gen->textures->c->b = ft_atoi(color[2]);
	}
	else if (dir == 'F')
	{
		gen->textures->f = (t_RGB *)malloc(sizeof(t_RGB));
		gen->textures->f->r = ft_atoi(color[0]);
		gen->textures->f->g = ft_atoi(color[1]);
		gen->textures->f->b = ft_atoi(color[2]);
	}
}

void	save_color(t_general *gen, char dir, char *line, int j)
{
	char	*path;
	char	**color;

	path = ft_chrtrim(&line[j], ' ');
	color = ft_split(path, ',');
	gen->c_texture++;
	if (check_color(path, color) == 0)
	{
		make_null(gen, dir);
		free(path);
		free_array(color);
		return ;
	}
	assign_color(gen, dir, color);
	free(path);
	free_array(color);
}

int	check_valid_color(t_general *gen)
{
	if (gen->textures->c->r > 255 || gen->textures->c->r < 0)
		return (printf("Error\nInvalid color\n"));
	if (gen->textures->c->g > 255 || gen->textures->c->g < 0)
		return (printf("Error\nInvalid color\n"));
	if (gen->textures->c->b > 255 || gen->textures->c->b < 0)
		return (printf("Error\nInvalid color\n"));
	if (gen->textures->f->r > 255 || gen->textures->f->r < 0)
		return (printf("Error\nInvalid color\n"));
	if (gen->textures->f->g > 255 || gen->textures->f->g < 0)
		return (printf("Error\nInvalid color\n"));
	if (gen->textures->f->b > 255 || gen->textures->f->b < 0)
		return (printf("Error\nInvalid color\n"));
	return (0);
}

int	get_y(char *file)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"));
	while (1)
	{
		str = gnl(fd);
		if (str == NULL)
			break ;
		if (!first_str(str, "1"))
			i++;
		free(str);
	}
	close(fd);
	return (i);
}
