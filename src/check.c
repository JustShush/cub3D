/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:35:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 11:54:08 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_suffix(char *str)
{
	while (*str)
	{
		if (ft_strcmp(str, ".cub") == 0)
			return (0);
		str++;
	}
	return (1);
}

int	check_walls(char **map)
{
	//floodfill the wall to check if its all connected.
	(void) map;
	return (0);
}

/*	What to check:
	- Map's content (0,1 and one of N,S,E,W);
	- Closed map (Surrounded by walls);
	- Texture and color elements are valid;

	Elements (except map):
	- Can be separated by \n and spaces;
	- Can be in any order;
	- Start with respective identifier;*/
int	map_check(char **av)
{
	if (check_suffix(av[1]))
		return (printf("Error\nFile extension must be '.cub'\n"));

	//map_init(); transforms map into array
	return (0);
}