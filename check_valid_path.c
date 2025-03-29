#include "so_long.h"

void    check_valid_path(char **map)
{
    char    **map_copy;
    int     reachable[3] = {0, 0, 0}; // {Player, Exit, Collectibles}
    int     player_x;
    int     player_y;
    int     i;
    int     j;
    int count_c;
    
    count_c = 0;
    i = 0;
    map_copy = copy_map(map);
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                player_x = j;
                player_y = i;
            }
            if (map[i][j] == 'C')
                count_c++;
            j++;
        }
        i++;
    }
    flood_fill(map_copy, player_x, player_y, reachable);
    printf("rechable %d count %d\n", reachable[2] ,count_c);
    if (reachable[1] != 1 || reachable[2] != count_c)
    {
        free_map(map);
        free_map(map_copy);
        error_exit("Error\nMap elements are not reachable.");
    } 
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
    {
        free_map(map);
        error_exit("Error\nMemory allocation failed.");
    } 
    i = 0;
    while (i < rows)
    {
        map_copy[i] = ft_strdup(map[i]);
        if (!map_copy[i])
        {
            i -= 1;
            while (i >= 0)
                free(map_copy[i--]);
            free_map(map);
            free_map(map_copy);
            error_exit("Error\nMemory allocation failed.");
        }    
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
    if (x < 0 || y < 0 || map[y][x] == '\0' || map[y][x] == '1' || map[y][x] == 'V')
        return;
    if (map[y][x] == 'P')
        reacheble[0] = 1;
    else if (map[y][x] == 'C')
        reacheble[2] += 1;    
    else if (map[y][x] == 'E')
        reacheble[1]++;
    map[y][x] = 'V'; // Mark as visited
    flood_fill(map, x + 1, y, reacheble); //right
    flood_fill(map, x - 1 , y, reacheble); //left
    flood_fill(map, x, y + 1, reacheble); //up
    flood_fill(map, x, y - 1, reacheble); // down
}