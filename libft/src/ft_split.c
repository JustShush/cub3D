/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:16:44 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:47:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Counts how many strings the array should contain

int	splitcount(char const *s, char c)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

//	Separates and returns the first instance of the delimited string
//	at the location pointed to by 's'

char	*splitmake(const char *s, char c)
{
	char	*buff;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	buff = (char *) malloc (sizeof(char) * (i + 1));
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s, i + 1);
	return (buff);
}

void	*splitfree(char **buff, int n)
{
	while (n > 0)
		free (buff[--n]);
	free (buff);
	return (NULL);
}

//	Returns an array of strings obtained by splitting 's' using the
//	character 'c' as a delimiter

char	**ft_split(char const *s, char c)
{
	char	**buff;
	char	*content;
	int		i;
	int		n;

	buff = (char **)malloc(sizeof(char *) * splitcount(s, c));
	if (!buff)
		return (NULL);
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			content = splitmake(s + i, c);
			if (!content)
				return (splitfree(buff, n));
			buff[n++] = content;
			while (s[i + 1] && s[i + 1] != c)
				i++;
		}
		i++;
	}
	buff[n] = NULL;
	return (buff);
}
