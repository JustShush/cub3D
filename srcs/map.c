//
// Created by ldiogo on 1/24/24.
//

#include "../get_next_line/get_next_line.h"

void	readmap(char **map, char *file)
{
    int		fd;
    int		i;
    char	*line;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error - Map not found\n");
        close(fd);
        return;
    }
    line = get_next_line(fd);
    while (line)
    {
        map[i] = ft_strdup(line);
        free(line);
        i++;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    close(fd);
}

int	numberoflines(char *file)
{
    int		fd;
    int		i;
    char	*line;

    i = 0;
    fd = open(file, O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        i++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return (i);
}

char    **map_init(char *file)
{
    char   **map;
    int i;

    i = 0;
    map = (char **)malloc(sizeof(char *) * (numberoflines(file) + 1));
    if (!map)
        return NULL;
    readmap(map, file);
    return (map);
}