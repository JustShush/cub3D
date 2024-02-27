/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/27 13:53:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	flood_fill(char **map, int x, int y, int lines)
{
	if (x >= 0 && y >= 0 && x < lines && y < ft_strlen(map[x]) && map[x][y] == '0')
	{
		map[x][y] = '1';
		if (flood_fill(map, x + 1, y, lines) == 1)
			return (1);
		if (flood_fill(map, x - 1, y, lines) == 1)
			return (1);
		if (flood_fill(map, x, y + 1, lines) == 1)
			return (1);
		if (flood_fill(map, x, y - 1, lines) == 1)
			return (1);
	}
	else if (x >= 0 && y >= 0 && x < lines && y < ft_strlen(map[x]) && map[x][y] == '1')
		return (0);
	else if (x < 0 || y < 0 || x >= lines || y >= ft_strlen(map[x]) || (map[x][y] != '1'
		&& map[x][y] != 'E' && map[x][y] != 'W'
		&& map[x][y] != 'N' && map[x][y] != 'S'))
		return (1);
	return (2);
}

int	check_map_closed(t_map *map, char **bmap)
{
	int	i;
	int	j;

	i = get_start_map(bmap);
	if (i + 1 < 0 || !bmap[i + 1] 
		|| first_str(bmap[i + 1], "1"))
		return (1);
	while (bmap[++i])
	{
		j = -1;
		while (bmap[i][++j])
		{
			if (bmap[i][j] == '0')
			{
				if (flood_fill(bmap, i, j, map->y + i) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	check_char(char **map)
{
	int	i;
	int	j;
	int	check;

	i = get_start_map(map);
	check = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'N' || map[i][j] == 'S'))
				check++;
			else if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '\t')
				return (printf(
						"Error\nMap is not valid - Invalid character found\n"));
			j++;
		}
		i++;
	}
	if (check != 1)
		return (printf("Error\nMap is not valid - Wrong player count\n"));
	return (1);
}

int	check_color(char *line, char **color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (color[i] == NULL)
			return (0);
		i++;
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			j++;
		if ((line[i] > '9' || line[i] < '0') && line[i] != ',')
			return (0);
		i++;
	}
	if (j != 2)
		return (0);
	return (1);
}

// void	free_test(t_general *gen)
// {
// 	int i = 0;
// 	while (++i < 13)
// 		mlx_destroy_image(gen->mlx, gen->anim[i].img);
// 	free(gen->anim);
// 	free(gen->textures->f);
// 	free(gen->textures->c);
// 	mlx_destroy_display(gen->mlx);
// 	free_array(gen->map->tilemap);
// 	free_array(gen->file);
// 	free(gen->key);
// 	free(gen->player);
// 	free(gen->img);
// 	free(gen->textures);
// 	free(gen->map);
// 	free(gen->mlx);
// 	free(gen);
// }

int	check_map(t_general *gen)
{
	get_textures(gen);
	if (!gen->file || check_map_closed(gen->map, gen->file) == 1)
	{
		printf("Error\nMap is not valid\n");
		exit_free_check(gen);

	}
	else if (check_textures(gen) || check_char(gen->file) != 1)
	{
		exit_free_check(gen);
	}
	else if (check_valid_color(gen))
	{
		printf("Error\nMap is not valid\n");
		exit_free_check(gen);

	}
	return (1);
}
