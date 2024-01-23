/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:48:42 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/23 12:47:15 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	check_next_line(char *res)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = 0;
	j = 0;
	while (res[i])
	{
		if (n == 1)
			res[j++] = res[i];
		if (res[i] == '\n')
			n = 1;
		res[i++] = '\0';
	}
	return (n);
}

char	*get_lines(char *line, char *res)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(res) + 1));
	while (line && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	while (*res)
	{
		temp[i++] = *res;
		if (*res++ == '\n')
			break ;
	}
	temp[i] = '\0';
	free(line);
	return (temp);
}

/*
ft_strlen
	15: Finds the lenght of the string until "\n" occurs (including \n)
check_next_line
	42: Checks if string has an "\n". 
	44: Deletes all characters that made it into "line" from res including "\n" 
	40: If there is an "\n", copies the character after "\n" (the ones that
		didn't make it to "line" from res) to the front of res.
	Example: buffer_size = 5
	res = abc\ne
	line = abc\n
	check_next_line(res)
	res = e0000
	return (1)
get_lines
	55: Allocates lenght of line + lenght of res to temp. Explanation: If for
		for example buffer_size = 2 and the 1st line is abcdefghi\nabc ,it will
		build line 2 characters at a time (line= 0 + 2 = 2 + 2 = 4 + 2 = 6...)
		until it reaches "\n" when it will be checked by check_next_line, find
		"\n" and break the while(in get_next_line).
*/