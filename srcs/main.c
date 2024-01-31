//
// Created by ldiogo on 1/24/24.
//

#include "../inc/buc3d.h"

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

void    save_img(t_general *gen, char *dir, char *line, int j)
{
	char *path;
	int fd;
	int x;
	int y;

	path = ft_strtrim(&line[j], ' ');
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

	path = ft_strtrim(&line[j], ' ');
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
    while(gen->map[i])
	{
        j = 0;
        while (gen->map[i][j])
        {
			while(gen->map[i][j] == ' ')
				j++;
			if(gen->map[i][j] == 'N' && gen->map[i][j + 1] == 'O' && gen->map[i][j + 2] == ' ')
				save_img(gen, "NO", gen->map[i], j + 2);
			else if(gen->map[i][j] == 'S' && gen->map[i][j + 1] == 'O' && gen->map[i][j + 2] == ' ')
				save_img(gen, "SO", gen->map[i], j + 2);
			else if(gen->map[i][j] == 'W' && gen->map[i][j + 1] == 'E' && gen->map[i][j + 2] == ' ')
				save_img(gen, "WE", gen->map[i], j + 2);
			else if(gen->map[i][j] == 'E' && gen->map[i][j + 1] == 'A' && gen->map[i][j + 2] == ' ')
				save_img(gen, "EA", gen->map[i], j + 2);
			else if(gen->map[i][j] == 'C' && gen->map[i][j + 1] == ' ')
				save_color(gen, 'C', gen->map[i], j + 1);
			else if(gen->map[i][j] == 'F' && gen->map[i][j + 1] == ' ')
				save_color(gen, 'F', gen->map[i], j + 1);
			break;
        }
		i++;
    }
	return 1;
}

int check_textures(t_general *gen)
{
	if(gen->textures->NO == NULL)
	{
		printf("Error - NO texture not found\n");
		return 0;
	}
	if(gen->textures->SO == NULL)
	{
		printf("Error - SO texture not found\n");
		return 0;
	}
	if(gen->textures->WE == NULL)
	{
		printf("Error - WE texture not found\n");
		return 0;
	}
	if(gen->textures->EA == NULL)
	{
		printf("Error - EA texture not found\n");
		return 0;
	}
	if(gen->textures->C == NULL)
	{
		printf("Error - C color not found\n");
		return 0;
	}
	if(gen->textures->F == NULL)
	{
		printf("Error - F color not found\n");
		return 0;
	}
	return 1;
}

int check_valid_color(t_general *gen)
{
	if(gen->textures->C->r > 255 || gen->textures->C->r < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	if(gen->textures->C->g > 255 || gen->textures->C->g < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	if(gen->textures->C->b > 255 || gen->textures->C->b < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	if(gen->textures->F->r > 255 || gen->textures->F->r < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	if(gen->textures->F->g > 255 || gen->textures->F->g < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	if(gen->textures->F->b > 255 || gen->textures->F->b < 0)
	{
		printf("Error - Invalid color\n");
		return 0;
	}
	return 1;
}

int check_map(t_general *gen)
{
	get_textures(gen);
	if(check_textures(gen) == 0 || check_valid_color(gen) == 0 || check_char(gen->map) == 0)
		return 0;
	if (check_map_closed(gen->map) == 1)
	{
		printf("Error - Map is not valid (Map is not closed 2)\n");
		return 0;
	}
	return 1;
}

int main(int argc, char **argv)
{
	t_general *gen;

	gen = (t_general *)malloc(sizeof(t_general));
    gen->textures = (t_textures *)malloc(sizeof(t_textures));
	gen->textures->C = (t_RGB *)malloc(sizeof(t_RGB));
	gen->textures->F = (t_RGB *)malloc(sizeof(t_RGB));
    if(argc != 2)
        return 0;
	gen->mlx = mlx_init();
	gen->map = map_init(argv[1]);
	if(check_map(gen) == 0)
		return 0;
	gen->win = mlx_new_window(gen->mlx, 1360, 768, "Buc3d");
    mlx_loop(gen->mlx);
    return (0);
}