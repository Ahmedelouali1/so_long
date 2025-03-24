/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:02:53 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/24 23:45:47 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>~

void    check_all(char **map);
void    check_rectangular(char **map);
void    check_walls(char **map);
void    check_map(char **map);
void    check_valid_path(char **map);
char    **copy_map(char **map);
void    flood_fill(char **map, int x, int y, int *reacheble);
void    free_map(char **map);
char    **read_map(const char fl);

#endif