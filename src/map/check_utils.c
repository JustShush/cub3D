/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:15 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/28 13:53:52 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	support_check_map(char **copy, int i, int j, t_map *map)
{
	while (copy[++i])
	{
		j = -1;
		while (copy[i][++j])
		{
			if (copy[i][j] == '0')
			{
				if (flood_fill(copy, i, j, map->y + i) == 1)
				{
					free_array(copy);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	flood_fill_support(char **map, int x, int y, int lines)
{
	if (flood_fill(map, x + 1, y, lines) == 1)
		return (1);
	if (flood_fill(map, x - 1, y, lines) == 1)
		return (1);
	if (flood_fill(map, x, y + 1, lines) == 1)
		return (1);
	if (flood_fill(map, x, y - 1, lines) == 1)
		return (1);
	if (flood_fill(map, x + 1, y + 1, lines) == 1)
		return (1);
	if (flood_fill(map, x - 1, y - 1, lines) == 1)
		return (1);
	if (flood_fill(map, x + 1, y - 1, lines) == 1)
		return (1);
	if (flood_fill(map, x - 1, y + 1, lines) == 1)
		return (1);
	return (0);
}

int	flood_fill(char **map, int x, int y, int lines)
{
	if (x >= 0 && y >= 0 && x < lines && y < ft_strlen(map[x])
		&& (map[x][y] == '0' || map[x][y] == 'E'
		|| map[x][y] == 'W' || map[x][y] == 'N'
		|| map[x][y] == 'S'))
	{
		map[x][y] = '1';
		if (flood_fill_support(map, x, y, lines) == 1)
			return (1);
	}
	else if (x >= 0 && y >= 0 && x < lines
		&& y < ft_strlen(map[x]) && map[x][y] == '1')
		return (0);
	else if (x < 0 || y < 0 || x >= lines
		|| y >= ft_strlen(map[x]) || (map[x][y] != '1'
		&& map[x][y] != 'E' && map[x][y] != 'W'
		&& map[x][y] != 'N' && map[x][y] != 'S'))
		return (1);
	return (2);
}

char	**copy_array(char **array)
{
	int		i;
	char	**new;

	i = 0;
	while (array[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	first_char(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == c)
		return (1);
	return (0);
}
