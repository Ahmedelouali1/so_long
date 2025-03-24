/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:19:11 by ahmel-ou          #+#    #+#             */
/*   Updated: 2024/12/29 18:54:37 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    check_valid_path(char **map)
{
    char    **map_copy;
    int     reachable[3] = {0, 0, 0}; // {Player, Exit, Collectibles}
    int     player_x;
    int     player_y;
    int     i;
    int     j;
    
    player_x = -1;
    player_y = -1;
    i = 0;
    map_copy = copy_map(map);

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                player_x = i;
                player_y = j;
                break;
            }
            j++;
        }
        if (player_x != -1)
            break;
        i++;
    }
    if (player_x == -1 || player_y == -1)
        error_exit("Error\nPlayer starting position not found.");
    flood_fill(map_copy, player_x, player_y, reachable);
    if (!reachable[1] || !reachable[2])
        error_exit("Error\nMap elements are not reachable.");
    free_map(map_copy);
}

char    **copy_map(char **map)
{
    char    **map_copy;
    int     rows;
    int     i;

    rows = 0;
    while (map[rows])
            rows++;
    map_copy = (char **)malloc(sizeof(char *) * (rows + 1));
    if (!map_copy)
        error_exit("Error\nMemory allocation failed.");
    i = 0;
    while (i < rows)
    {
        map_copy[i] = ft_strdup(map[i]);
        if (!map_copy[i])
            error_exit("Error\nMemory allocation failed.");
        i++;
    }
    map_copy[i] = NULL;
    return (map_copy);
}
void    free_map(char **map)
{
    int     i;
    
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}
void    flood_fill(char **map, int x, int y, int *reacheble)
{
    if (x < 0 || y < 0 || !map[x][y] == '\0' || map[x][y] == '1' || map[x][y] == 'V')
        return;
    if (map[x][y] == 'P')
        reacheble[0] = 1;
    else if (map[x][y] == 'C')
        reacheble[1] = 1;
    else if (map[x][y] == 'E')
        reacheble[2]++;
    map[x][y] = 'V'; // Mark as visited
    flood_fill(map, x + 1, y, reacheble); //right
    flood_fil(map, x - 1 , y, reacheble); //left
    flood_fill(map, x, y + 1, reacheble); //up
    flood_fill(map, x, y - 1, reacheble); // down
}