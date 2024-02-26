/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:30:14 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	if (map[x] && map[x][y] == '0')
	{
		map[x][y] = '1';
		if (flood_fill(map, x + 1, y) == 1)
			return (1);
		if (flood_fill(map, x - 1, y) == 1)
			return (1);
		if (flood_fill(map, x, y + 1) == 1)
			return (1);
		if (flood_fill(map, x, y - 1) == 1)
			return (1);
	}
	else if (map[x] && map[x][y] == '1')
		return (0);
	else if ((map[x] && map[x][y] != '1' && map[x][y] != 'E'
		&& map[x][y] != 'W' && map[x][y] != 'N' && map[x][y] != 'S')
		|| (!map[x] || !map[x][y]))
	{
		printf("Error - Map is not valid (Map is not closed 1)\n");
		return (1);
	}
	return (2);
}

int	check_map_closed(char **map)
{
	int	i;
	int	j;

	i = get_start_map(map) - 1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (flood_fill(map, i, j) == 1)
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
						"Error - Map is not valid (Invalid character found)\n"));
			j++;
		}
		i++;
	}
	if (check != 1)
		return (printf("Error - Map is not valid (Wrong player count)\n"));
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

int	check_map(t_general *gen)
{
	get_textures(gen);
	if (check_map_closed(gen->file) == 1)
	{
		printf("Error - Map is not valid (Map is not closed 2)\n");
		exit_free_check(gen);
		return (0);
	}
	if (check_textures(gen) || check_valid_color(gen)
		|| check_char(gen->file) != 1)
	{
		printf("Error - Map is not valid (Invalid color)\n");
		exit_free_check(gen);
		return (0);
	}
	return (1);
}
