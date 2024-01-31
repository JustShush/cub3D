#include "../inc/buc3d.h"

void    printf_array(char **array)
{
	int i = 0;
	while(array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char *ft_strtrim(char *line, char c)
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

int ft_atoi(char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;
	while(str[i] == ' ')
		i++;
	if(str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while(str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return res * sign;
}