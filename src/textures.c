/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:48:14 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/28 14:47:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_img	*init_texture(t_general *gen, char *path)
{
	t_img	*texture;

	texture = (t_img *)malloc(sizeof(t_img));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(gen->mlx, path,
			&(texture->width), &(texture->height));
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bits_per_pixel),
			&(texture->line_length), &(texture->endian));
	return (texture);
}

void	save_img(t_general *gen, char *dir, char *line, int j)
{
	char	*path;
	int		fd;

	gen->c_texture++;
	path = ft_chrtrim(&line[j], ' ');
	fd = open(path, O_RDONLY);
	if (fd == -1 || check_suffix(path, ".xpm"))
	{
		if (check_suffix(path, ".xpm"))
			close(fd);
		free(path);
		return ;
	}
	close(fd);
	if (dir[0] == 'N' && dir[1] == 'O' && gen->textures->no == NULL)
		gen->textures->no = init_texture(gen, path);
	else if (dir[0] == 'S' && dir[1] == 'O' && gen->textures->so == NULL)
		gen->textures->so = init_texture(gen, path);
	else if (dir[0] == 'W' && dir[1] == 'E' && gen->textures->we == NULL)
		gen->textures->we = init_texture(gen, path);
	else if (dir[0] == 'E' && dir[1] == 'A' && gen->textures->ea == NULL)
		gen->textures->ea = init_texture(gen, path);
	free(path);
}

void	save_textures(t_general *gen, int i, int j)
{
	if (gen->file[i][j] == 'N' && gen->file[i][j + 1] == 'O'
		&& gen->file[i][j + 2] == ' ')
		save_img(gen, "NO", gen->file[i], j + 2);
	else if (gen->file[i][j] == 'S' && gen->file[i][j + 1] == 'O'
		&& gen->file[i][j + 2] == ' ')
		save_img(gen, "SO", gen->file[i], j + 2);
	else if (gen->file[i][j] == 'W' && gen->file[i][j + 1] == 'E'
		&& gen->file[i][j + 2] == ' ')
		save_img(gen, "WE", gen->file[i], j + 2);
	else if (gen->file[i][j] == 'E' && gen->file[i][j + 1] == 'A'
		&& gen->file[i][j + 2] == ' ')
		save_img(gen, "EA", gen->file[i], j + 2);
	else if (gen->file[i][j] == 'C' && gen->file[i][j + 1] == ' ')
		save_color(gen, 'C', gen->file[i], j + 1);
	else if (gen->file[i][j] == 'F' && gen->file[i][j + 1] == ' ')
		save_color(gen, 'F', gen->file[i], j + 1);
	else if (line_empty(gen->file[i]) == 0)
		exit_free_check(gen, "Error\nInvalid line in file");
}

int	get_textures(t_general *gen)
{
	int	i;
	int	j;

	i = 0;
	while (gen->file[i])
	{
		j = 0;
		if (first_char(gen->file[i], '1') == 1)
			break ;
		while (gen->file[i][j])
		{
			while (gen->file[i][j] == ' ')
				j++;
			save_textures(gen, i, j);
			break ;
		}
		i++;
	}
	return (0);
}

int	check_textures(t_general *gen)
{
	if (gen->textures->no == NULL)
		return (printf("Error\nNO texture not found\n"));
	if (gen->textures->so == NULL)
		return (printf("Error\nSO texture not found\n"));
	if (gen->textures->we == NULL)
		return (printf("Error\nWE texture not found\n"));
	if (gen->textures->ea == NULL)
		return (printf("Error\nEA texture not found\n"));
	if (gen->textures->c == NULL)
		return (printf("Error\nC color not found\n"));
	if (gen->textures->f == NULL)
		return (printf("Error\nF color not found\n"));
	return (0);
}
