/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:24:02 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/31 13:08:31 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	printf_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		printf("%s", array[i]);
		i++;
	}
}

char	*ft_chrtrim(char *line, char c)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	while(line[i] == c)
		i++;
	j = i;
	while(line[j] != c && line[j])
		j++;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if(!str)
		return NULL;
	j = 0;
	while(line[i] != c && line[i] && line[i] != '\n')
	{
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return str;
}