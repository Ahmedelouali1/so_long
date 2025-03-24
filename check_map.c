/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:13:13 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/24 21:50:14 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_all(char **map)
{
	check_characters_and_elements(map);
	check_rectangular(map);
	check_walls(map);
	chack_valid_path(map);
}
void    check_rectangular(char **map)
{
	int	i;
	int	row_len;

	i = 0;
	row_len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != row_len)
			error_exit("Error\nMap is not rectangular.");
		i++;
	}
}
void	check_walls(char **map)
{
	int	i;
	int	j;
	int	rows;

	i = 0;
	rows = 0;
	while (map[rows])
		rows++;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1')
			error_exit("Error\nMap is not surrounded by walls.");
	}
	j = 0;
	while (map[rows - 1][j])
	{
		if (map[rows - 1] != '1')
			error_exit("Error\nMap is not surrounded by walls.");
	}
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			error_exit("Error\nMap is not surrounded by walls.");
		i++;
	}
}
void	check_map(char **map)
{
	int i;
	int player_count;
	int exit_count;
	int coll_count;
	int j;

	i = 0;
	player_count = 0;
	exit_count = 0;
	coll_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				player_count++;
			else if (map[i][j] == 'E')
				exit_count++;
			else if (map[i][j] == 'C')
				coll_count++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				error_exit("Eroor\nInvalid map character.");
			j++;
		}
		i++;
	}
	if (player_count != 1 || exit_count < 1 || coll_count < 1)
		error_exit("Error\nInvalid map elements.");
	return (1);
}