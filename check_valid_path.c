#include "so_long.h"

void	start_floodf_fill(int p_x, int p_y, int count_c, char **map)
{
	char	**map_copy;
	static int reachable[3]; // {Player, Exit, Collectibles}

	map_copy = copy_map(map);
	flood_fill(map_copy, p_x, p_y, reachable);
	if (reachable[1] != 1 || reachable[2] != count_c)
	{
		free_map(map);
		free_map(map_copy);
		error_exit("Error\nMap elements are not reachable.");
	}
	free_map(map_copy);
}

void	check_valid_path(char **map, int i, int j)
{
	int	p_x;
	int	p_y;
	int	count_c;

	count_c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				p_x = j;
				p_y = i;
			}
			if (map[i][j] == 'C')
				count_c++;
			j++;
		}
		i++;
	}
	start_floodf_fill(p_x, p_y, count_c, map);
}

void	dup_failure(char **map_copy, char **map, int i)
{
	i -= 1; 
	while (i >= 0)
		free(map_copy[i--]);
	free_map(map);
	free_map(map_copy);
	error_exit("Error\nMemory allocation failed.");
}

char	**copy_map(char **map)
{
	char	**map_copy;
	int		rows;
	int		i;

	rows = 0;
	while (map[rows])
		rows++;
	map_copy = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!map_copy)
	{
		free_map(map);
		error_exit("Error\nMemory allocation failed.");
	}
	i = 0;
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
            dup_failure(map_copy, map, i);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
void	flood_fill(char **map, int x, int y, int *reacheble)
{
	if (x < 0 || y < 0 || map[y][x] == '\0' || map[y][x] == '1'
		|| map[y][x] == 'V')
		return ;
	if (map[y][x] == 'P')
		reacheble[0] = 1;
	else if (map[y][x] == 'C')
		reacheble[2] += 1;
	else if (map[y][x] == 'E')
		reacheble[1]++;
	map[y][x] = 'V';                      // Mark as visited
	flood_fill(map, x + 1, y, reacheble); // right
	flood_fill(map, x - 1, y, reacheble); // left
	flood_fill(map, x, y + 1, reacheble); // up
	flood_fill(map, x, y - 1, reacheble); // down
}
