/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:02 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/22 10:29:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	sizeofmap_x(t_general *gen)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = 0;
	while (gen->map->tilemap[i])
	{
		j = 0;
		while (gen->map->tilemap[i][j])
			j++;
		if (j > res)
			res = j;
		i++;
	}
	return (i);
}

int	sizeofmap_y(t_general *gen)
{
	int	i;

	i = 0;
	while (gen->map->tilemap[i])
		i++;
	return (i - 1);
}

char	*ft_chrtrim(char *line, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] == c)
		i++;
	j = i;
	while (line[j] != c && line[j])
		j++;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (line[i] != c && line[i] && line[i] != '\n')
	{
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	get_start_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i -= 1;
	while (line_empty(map[i]) == 1)
		i--;
	while (line_empty(map[i]) == 0)
		i--;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
