/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:35:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/25 13:02:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Checks if file_path has ".cub" suffix
int	check_suffix(char *file_path)
{
	while (*file_path)
	{
		if (ft_strcmp(file_path, ".cub") == 0)
			return (0);
		file_path++;
	}
	return (1);
}

//I thought a good way to check if the game is closed, was to use floodfill
// on the 1s at the wall to see if they are all connected.
// The ideia is to change all the "1" to "i" and then check if there are any "1"
// left at the walls. Idk if it'll work though.
/* int	check_walls(t_map *map, int x, int y)
{
	if (x >= 0 && y >= 0 && y < map->y && x < (int)ft_strlen(map->tilemap[y])
		&& map->tilemap[y][x] == '1')
	{
		map->tilemap[y][x] = 'i';
		check_walls(map, x + 1, y);
		check_walls(map, x - 1, y);
		check_walls(map, x, y + 1);
		check_walls(map, x, y - 1);
	}
	return (0);
} */

/*	What to check:
	- Map's content (0,1 and one of N,S,E,W);
	- Closed map (Surrounded by walls);
	- Texture and color elements are valid;

	Elements (except map):
	- Can be separated by \n and spaces;
	- Can be in any order;
	- Start with respective identifier;*/
int	map_check(t_map *map, char **av)
{
	if (check_suffix(av[1]))
		return (printf("Error\nFile extension must be '.cub'\n"));
	if (map_init(map, av[1]))
		return (printf("Error\nMap Init\n"));
	/* 	if (check_walls(map, 0, 0))
		return (0); */
	return (0);
}