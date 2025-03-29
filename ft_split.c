#include "so_long.h"

int	ft_count(char *s, char c)
{
	size_t	i;
	size_t	contain_c;

	i = 0;
	contain_c = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			contain_c++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (contain_c);
}

char	*word_traitement(char *s, char c)
{
	char	*temp;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	**ft_split(char *s, char c)
{
	int		b;
	char	**all;

	b = 0;
	all = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!all)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			all[b] = word_traitement(s, c);
			if (!all[b])
			{
				free_map(all);
				return (NULL);
			}	
			b++;
			while (*s && *s != c)
				s++;
		}
	}
	all[b] = NULL;
	return (all);
}