/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:02:53 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/31 07:52:21 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESC_KEY 65307


typedef struct game_s
{
	void	*conx;
	void	*window;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
	void	*background;
    void *holya;
	char	**map;
	int		p_x;
	int		p_y;
	int		count;
    int     width;
    int     heigth;
    int holya_w;
    int holya_h;
    
}			game_t;

int			check_extension(char *str);
char		**read_map(char *fl);
char		**ft_split(char *s, char c);
int			ft_strlen(char *s);
char		*ft_strjoin(char *s1, char *s2);
void		check_all(char **map);
void		check_valid_path(char **map, int i, int j);
void		free_map(char **map);
void		error_exit(char *msg);
char		**copy_map(char **map);
void		free_map(char **map);
void		flood_fill(char **map, int x, int y, int *reacheble);
void		check_rectangular(char **map);
void		check_walls(char **map);
int			check_map(char **map);
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s);
char		*ft_strchr(char *str, int c);
char		*ft_substr(char *s, int start, int len);
int			ft_destroy(void *param);

#endif