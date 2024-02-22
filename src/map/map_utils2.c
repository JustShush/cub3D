/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:29:36 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:31:59 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	save_color(t_general *gen, char dir, char *line, int j)
{
	char	*path;
	char	**color;

	path = ft_chrtrim(&line[j], ' ');
	color = ft_split(path, ',');
	if (check_color(path) == 0)
		return ;
	if (dir == 'C')
	{
		gen->textures->c->r = ft_atoi(color[0]);
		gen->textures->c->g = ft_atoi(color[1]);
		gen->textures->c->b = ft_atoi(color[2]);
	}
	else if (dir == 'F')
	{
		gen->textures->f->r = ft_atoi(color[0]);
		gen->textures->f->g = ft_atoi(color[1]);
		gen->textures->f->b = ft_atoi(color[2]);
	}
	free(path);
	free_array(color);
}

int	check_valid_color(t_general *gen)
{
	if (gen->textures->c->r > 255 || gen->textures->c->r < 0)
		return (printf("Error - Invalid color\n"));
	if (gen->textures->c->g > 255 || gen->textures->c->g < 0)
		return (printf("Error - Invalid color\n"));
	if (gen->textures->c->b > 255 || gen->textures->c->b < 0)
		return (printf("Error - Invalid color\n"));
	if (gen->textures->f->r > 255 || gen->textures->f->r < 0)
		return (printf("Error - Invalid color\n"));
	if (gen->textures->f->g > 255 || gen->textures->f->g < 0)
		return (printf("Error - Invalid color\n"));
	if (gen->textures->f->b > 255 || gen->textures->f->b < 0)
		return (printf("Error - Invalid color\n"));
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
