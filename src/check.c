/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:35:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/30 13:22:27 by ddiniz-m         ###   ########.fr       */
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

int	map_check(t_map *map, char **av)
{
	if (check_suffix(av[1]))
		return (printf("Error\nFile extension must be '.cub'\n"));
	if (map_init(map, av[1]))
		return (printf("Error\nMap Init\n"));
	return (0);
}