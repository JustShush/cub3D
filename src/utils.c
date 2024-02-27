/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:21:27 by mira              #+#    #+#             */
/*   Updated: 2024/02/27 10:25:35 by ddiniz-m         ###   ########.fr       */
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

int	line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

//Return 0 if file_path has suffix
int	check_suffix(char *file_path, char *suf)
{
	while (*file_path)
	{
		if (ft_strcmp(file_path, suf) == 0)
			return (0);
		file_path++;
	}
	return (1);
}
