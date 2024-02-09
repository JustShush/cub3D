/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:27 by mira              #+#    #+#             */
/*   Updated: 2024/02/09 13:27:34 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Returns 0 if s1's first non space chars are equal to s2
int	first_str(char *s1, char *s2)
{
	while (*s1 == ' ')
		s1++;
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (0);
	return (1);
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
