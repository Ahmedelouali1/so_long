/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:13:13 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/31 08:15:13 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_all(char **map)
{
	check_rectangular(map);
	check_walls(map);
	check_map(map);
	check_valid_path(map, 0, 0);
}
void	check_rectangular(char **map)
{
	int	i;
	int	row_len;

	i = 0;
	row_len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != row_len)
		{
			free_map(map);
			error_exit("Error\nMap is not rectangular.");
		}
		i++;
	}
	if (row_len > 64 || i > 33)
	{
		free_map(map);
		error_exit("Error\nMap is too big!!");
	}
}
void	check_lines(char **map, int rows)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (map[0][j++] != '1')
		{
			free_map(map);
			error_exit("Error\nMap is not surrounded by walls.");
		}
	}
	j = 0;
	while (map[rows - 1][j])
	{
		if (map[rows - 1][j++] != '1')
		{
			free_map(map);
			error_exit("Error\nMap is not surrounded by walls.");
		}
	}
}

void	check_walls(char **map)
{
	int	i;
	int	rows;

	rows = 0;
	while (map[rows] != NULL)
		rows++;
	check_lines(map, rows);
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
		{
			free_map(map);
			error_exit("Error\nMap is not surrounded by walls.");
		}
		i++;
	}
}
void	map_char(char **map, int *p_count, int *e_count, int *c_count, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == 'P')
			(*p_count)++;
		else if (map[i][j] == 'E')
			(*e_count)++;
		else if (map[i][j] == 'C')
			(*c_count)++;
		else if (map[i][j] != '1' && map[i][j] != '0')
		{
			free_map(map);
			error_exit("Eroor\nInvalid map character.");
		}
		j++;
	}
}

int	check_map(char **map)
{
	int	i;
	int	p_count;
	int	e_count;
	int	c_count;
	
	i = 0;
	p_count = 0;
	e_count = 0;
	c_count = 0;
	while (map[i])
	{
		map_char(map, &p_count, &e_count, &c_count, i);
		i++;
	}
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		free_map(map);
		error_exit("Error\nInvalid map elements.");
	}
	return (1);
}
