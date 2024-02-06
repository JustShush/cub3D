/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/06 13:01:12 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	if (map[x] && map[x][y] == '0')
	{
		map[x][y] = '1';
		if(flood_fill(map, x + 1, y) == 1)
			return 1;
		if(flood_fill(map, x - 1, y) == 1)
			return 1;
		if(flood_fill(map, x, y + 1) == 1)
			return 1;
		if(flood_fill(map, x, y - 1) == 1)
			return 1;
	}
	else if (map[x] && map[x][y] == '1')
		return 0;
	else if (map[x] && map[x][y] != '1' && map[x][y] != 'E' && map[x][y] != 'W' && map[x][y] != 'N' && map[x][y] != 'S')
	{
		printf("Error - Map is not valid (Map is not closed 1)\n");
		return 1;
	}
	else if (!map[x] || !map[x][y])
	{
		printf("Error - Map is not valid (Map is not closed 1)\n");
		return 1;
	}
	return 2;
}

int		check_map_closed(char **map)
{
	int	i;
	int	j;

	i = get_start_map(map) - 1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if(map[i][j] == '0')
			{
				if (flood_fill(map, i, j) == 1)
					return 1;
			}
		}
	}
	return 0;
}

int line_empty(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return 0;
		i++;
	}
	return 1;
}

int get_start_map(char **map)
{
	int i;

	i = 0;
	while(map[i])
		i++;
	i -= 1;
	while(line_empty(map[i]) == 1)
		i--;
	while(line_empty(map[i]) == 0)
		i--;
	return (i);

}

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

int check_char(char **map)
{
	int i;
	int j;
	int check;

	i = get_start_map(map);
	check = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if((map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'N' || map[i][j] == 'S'))
				check++;
			else if(map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '\n' && map[i][j] != ' ' && map[i][j] != '\t')
			{
				printf("Error - Map is not valid (Invalid character found)\n");
				return 0;
			}
			j++;
		}
		i++;
	}
	if(check != 1)
	{
		printf("Error - Map is not valid (Wrong player count)\n");
		return 0;
	}
	return 1;
}

void	save_img(t_general *gen, char *dir, char *line, int j)
{
	char *path;
	int fd;
	int x;
	int y;

	path = ft_chrtrim(&line[j], ' ');
	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		printf("Error - Invalid texture path\n");
		return;
	}
	close(fd);
	if (dir[0] == 'N' && dir[1] == 'O')
		gen->textures->NO = mlx_xpm_file_to_image(gen->mlx, path, &x, &y);
	else if (dir[0] == 'S' && dir[1] == 'O')
		gen->textures->SO = mlx_xpm_file_to_image(gen->mlx, path, &x, &y);
	else if (dir[0] == 'W' && dir[1] == 'E')
		gen->textures->WE = mlx_xpm_file_to_image(gen->mlx, path, &x, &y);
	else if (dir[0] == 'E' && dir[1] == 'A')
		gen->textures->EA = mlx_xpm_file_to_image(gen->mlx, path, &x, &y);
	printf("dir: %s\n", dir);
	free(path);
}

int check_color(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(line[i] != '\0')
	{
		if(line[i] == ',')
			j++;
		if((line[i] > '9' || line[i] < '0') && line[i] != ',')
			return 0;
		i++;
	}
	if(j != 2)
		return 0;
	return 1;
}

void	save_color(t_general *gen, char dir, char *line, int j)
{
	char *path;
	char **color;

	path = ft_chrtrim(&line[j], ' ');
	color = ft_split(path, ',');
	if(check_color(path) == 0)
		return ;
	if (dir == 'C')
	{
		gen->textures->C->r = ft_atoi(color[0]);
		gen->textures->C->g = ft_atoi(color[1]);
		gen->textures->C->b = ft_atoi(color[2]);
	}
	else if (dir == 'F')
	{
		gen->textures->F->r = ft_atoi(color[0]);
		gen->textures->F->g = ft_atoi(color[1]);
		gen->textures->F->b = ft_atoi(color[2]);
	}
}

int get_textures(t_general *gen)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(gen->file[i])
	{
		j = 0;
		while (gen->file[i][j])
		{
			while(gen->file[i][j] == ' ')
				j++;
			if(gen->file[i][j] == 'N' && gen->file[i][j + 1] == 'O' && gen->file[i][j + 2] == ' ')
				save_img(gen, "NO", gen->file[i], j + 2);
			else if(gen->file[i][j] == 'S' && gen->file[i][j + 1] == 'O' && gen->file[i][j + 2] == ' ')
				save_img(gen, "SO", gen->file[i], j + 2);
			else if(gen->file[i][j] == 'W' && gen->file[i][j + 1] == 'E' && gen->file[i][j + 2] == ' ')
				save_img(gen, "WE", gen->file[i], j + 2);
			else if(gen->file[i][j] == 'E' && gen->file[i][j + 1] == 'A' && gen->file[i][j + 2] == ' ')
				save_img(gen, "EA", gen->file[i], j + 2);
			else if(gen->file[i][j] == 'C' && gen->file[i][j + 1] == ' ')
				save_color(gen, 'C', gen->file[i], j + 1);
			else if(gen->file[i][j] == 'F' && gen->file[i][j + 1] == ' ')
				save_color(gen, 'F', gen->file[i], j + 1);
			break;
		}
		i++;
	}
	return 1;
}

int check_textures(t_general *gen)
{
	if(gen->textures->NO == NULL)
		return(printf("Error - NO texture not found\n"));
	if(gen->textures->SO == NULL)
		return(printf("Error - SO texture not found\n"));
	if(gen->textures->WE == NULL)
		return(printf("Error - WE texture not found\n"));
	if(gen->textures->EA == NULL)
		return(printf("Error - EA texture not found\n"));
	if(gen->textures->C == NULL)
		return(printf("Error - C color not found\n"));
	if(gen->textures->F == NULL)
		return(printf("Error - F color not found\n"));
	return (0);
}

int check_valid_color(t_general *gen)
{
	if(gen->textures->C->r > 255 || gen->textures->C->r < 0)
		return(printf("Error - Invalid color\n"));
	if(gen->textures->C->g > 255 || gen->textures->C->g < 0)
		return(printf("Error - Invalid color\n"));
	if(gen->textures->C->b > 255 || gen->textures->C->b < 0)
		return(printf("Error - Invalid color\n"));
	if(gen->textures->F->r > 255 || gen->textures->F->r < 0)
		return(printf("Error - Invalid color\n"));
	if(gen->textures->F->g > 255 || gen->textures->F->g < 0)
		return(printf("Error - Invalid color\n"));
	if(gen->textures->F->b > 255 || gen->textures->F->b < 0)
		return(printf("Error - Invalid color\n"));
	return (0);
}

int	check_map(t_general *gen)
{
	get_textures(gen);
	if (check_textures(gen) || check_valid_color(gen) || check_char(gen->file) == 0)
		return (0);
	if (check_map_closed(gen->file) == 1)
	{
		printf("Error - Map is not valid (Map is not closed 2)\n");
		return (0);
	}
	return (1);
}
