/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:52:53 by ahmel-ou          #+#    #+#             */
/*   Updated: 2024/12/24 18:07:52 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char    **read_map(const char fl)
{
    int fd;
    int read_bytes;
    char    *line;
    char    *tmp;
    char    *full_map;
    char    **map;
    
    *map = NULL;
    full_map = NULL;
    tmp = NULL;
    line = NULL;
    fd = open(fl, O_RDONLY);
    if (fd < 0)
        erro_exit("Error\nFailed to open map file.");
    while ((read_bytes = get_next_line(fd, &line)) > 0)
    {
        tmp = full_map;
        full_map = ft_str_join(tmp, line);
        free(tmp);
        free(line);
        tmp = full_map;
        full_map = ft_strjoin(tmp, "\n");
        free(tmp);
    }
    close(fd);
    if (!full_map)
        error_exit("Eroor\nEmpty map file.");
    map = ft_split(full_map, '\n');
    free(full_map);
    
}