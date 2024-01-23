/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:35:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 15:51:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	getY(int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		str = gnl(fd);
		if (str == NULL)
			break ;
		if (!first_str(str, "1"))
			i++;
		free(str);
	}
	return (i);
}

//This initizalizes map->tilemap to only have the actual map;
// Also initializes the map->(north, south, west and east) strings;
void	tilemap(t_map *map, char *map_path)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCould not open file\n");
		return ;
	}
	map->tilemap = malloc(sizeof(char *) * (map->y + 1));
	while (i < map->y)
	{
		buf = gnl(fd);
		if (!first_str(buf, "1"))
			map->tilemap[i++] = ft_strdup(buf);
		if (!first_str(buf, "NO"))
			map->north = ft_strdup(buf);
		if (!first_str(buf, "SO"))
			map->south = ft_strdup(buf);
		if (!first_str(buf, "WE"))
			map->west = ft_strdup(buf);
		if (!first_str(buf, "EA"))
			map->east = ft_strdup(buf);
		free(buf);
	}
	map->tilemap[i] = 0;
	return ;
}

//For now, this function opens the .cub file, finds the number of lines it has
//	and separates the elements in the respective arrays/str of the struct t_map
int	map_init(t_map *map, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCould not open file\n"));

	map->y = getY(fd);
	close(fd);

	tilemap(map, map_path);

	arr_print("TILEMAP", map->tilemap);
	printf("\nmap->north: %s", map->north);
	printf("map->west: %s", map->west);
	printf("map->east: %s", map->east);
	printf("map->south: %s", map->south);
	return (0);
}