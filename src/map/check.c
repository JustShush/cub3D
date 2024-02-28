/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/28 14:52:35 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_map_closed(t_map *map, char **bmap)
{
	int		i;
	int		j;
	char	**copy;

	j = 0;
	i = get_start_map(bmap);
	copy = copy_array(bmap);
	if (i + 1 < 0 || !bmap[i + 1] 
		|| first_str(bmap[i + 1], "1"))
	{
		free_array(copy);
		return (1);
	}
	if (support_check_map(copy, i, j, map) == 1)
		return (1);
	free_array(copy);
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
						"Error\nInvalid character found\n"));
			j++;
		}
		i++;
	}
	if (check != 1)
		return (printf("Error\nWrong player count\n"));
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

int	check_double_map(t_general *gen)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (gen->file[i])
	{
		if (first_char(gen->file[i], '1'))
			j++;
		i++;
	}
	i -= 1;
	while (i >= 0)
	{
		if (first_char(gen->file[i], '1'))
			k++;
		if (line_empty(gen->file[i]))
			break ;
		i--;
	}
	if (j != k)
		exit_free_check(gen, "Error\nInvalid Map");
	return (0);
}

int	check_map(t_general *gen)
{
	check_double_map(gen);
	get_textures(gen);
	if (!gen->file || check_map_closed(gen->map, gen->file) == 1
		|| gen->c_texture != 6)
		exit_free_check(gen, "Error\nInvalid map");
	else if (check_textures(gen) || check_char(gen->file) != 1)
	{
		exit_free_check(gen, NULL);
	}
	else if (check_valid_color(gen))
	{
		exit_free_check(gen, "Error\nInvalid Color");
	}
	return (1);
}
