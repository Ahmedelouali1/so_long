/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:52:53 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/30 06:45:31 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(0);
}

char	**read_map(char *fl)
{
	int		fd;
	char	**map;
	char	*gnl;
	char	*join_map;
	char	*tmp;

	fd = open(fl, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nFailed to open map file.");
	gnl = get_next_line(fd);
	join_map = NULL;
	while (gnl != NULL)
	{
		tmp = join_map;
		join_map = ft_strjoin(join_map, gnl);
		free(tmp);
		free(gnl);
		if (!join_map)
		{
			free(join_map);
			close(fd);
			error_exit("Error\nMalloc error");
		}
		gnl = get_next_line(fd);
	}
	map = ft_split(join_map, '\n');
	free(join_map);
	close(fd);
	return (map);
}
int	check_extension(char *str)
{
	int		i;
	char	*ber;
	int		j;

	j = 0;
	i = 0;
	if (ft_strlen(str) <= 4) //.ber
	{
		write(2, "Error\nIncorrect File Extension\n", 31);
		return (0);
	}
	i = ft_strlen(str) - 4;
	ber = ".ber";
	while (ber[j])
	{
		if (ber[j] != str[i])
		{
			write(2, "Error\nIncorrect File Extension\n", 31);
			return (0);
		}
		i++;
		j++;
	}
	return (1);
}

void	load_graphics(game_t *data)
{
	int	height;
	int	width;
	int	x;
	int	y;

	data->conx = NULL;
	data->window = NULL;
	data->wall = NULL;
	data->background = NULL;
	data->collectible = NULL;
	data->player = NULL;
	data->exit = NULL;
	width = ft_strlen(data->map[0]);
	height = 0;
	data->conx = mlx_init();
	while (data->map[height])
		height++;
	data->window = mlx_new_window(data->conx, 60 * width, 60 * height, "so_long");
	data->wall = mlx_xpm_file_to_image(data->conx, "./images/w.xpm", &x, &y);
	data->background = mlx_xpm_file_to_image(data->conx, "./images/b.xpm", &x, &y);
	data->collectible = mlx_xpm_file_to_image(data->conx, "./images/c.xpm", &x, &y);
	data->player = mlx_xpm_file_to_image(data->conx, "./images/p.xpm", &x, &y);
	data->exit = mlx_xpm_file_to_image(data->conx, "./images/e.xpm", &x, &y);
	// printf("conx :%p\n window : %p\nwall : %p\nbackground : %p\n collec %p\n player : %p", data->conx, data->window, data->wall, data->background, data->collectible, data->player);
}

void	draw_map(game_t *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			printf("%d i %d\n", i, j);
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->conx, data->window, data->wall, j * 60, i * 60);
			if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->conx, data->window, data->exit, j*60, i*60);
			if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->conx, data->window, data->collectible, j * 60, i * 60);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->conx, data->window, data->player, data->p_x*60, data->p_y*60 );
}
int	player_movements(int key, void *param)
{
	game_t	*data;

	data = (game_t *)param;
	if (key == W_KEY)
	{
		if(data->map[data->p_y - 1][data->p_x] != '1')
			data->p_y -= 1;
	}	
	if (key == A_KEY)
	{
		if(data->map[data->p_y][data->p_x - 1] != '1')
		data->p_x -= 1;
	}	
	if (key == S_KEY)
	{
		if(data->map[data->p_y + 1][data->p_x] != '1')
		data->p_y += 1;
	}	
	if (key == D_KEY)
	{
		if(data->map[data->p_y][data->p_x + 1] != '1')
		data->p_x += 1;
	}
	if (data->map[data->p_y][data->p_x] == 'C')
		data->map[data->p_y][data->p_x] = '0';
	
	mlx_clear_window(data->conx, data->window);
	draw_map(data);
	return (0);
}
void player_position(game_t *data)
{
	int i;
	int j;
	
	i = 0;
	while(data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->p_x = j;
				data->p_y = i;
			
				return;
			}
			j++;
		}
		i++;
	}
}
int ft_destroy(void *param)
{
	game_t *data;
	
	data = (game_t *)param;
	free_map(data->map);
	mlx_destroy_image(data->conx, data->background);
	mlx_destroy_image(data->conx, data->exit);
	mlx_destroy_image(data->conx, data->wall);
	mlx_destroy_image(data->conx, data->player);
	mlx_destroy_image(data->conx, data->collectible);
	mlx_destroy_window(data->conx, data->window);
	exit(0);
}

int	main(int argc, char *argv[])
{
	char **map;
	game_t data;

	if (argc != 2)
	{
		write(2, "Error\nIncorrect arguments\n", 26);
		return (0);
	}
	if (check_extension(argv[1]) == 0)
		return (0);
	map = read_map(argv[1]);
	check_all(map);
	data.map = map;
	load_graphics(&data);
	player_position(&data);
	draw_map(&data);
	
	mlx_key_hook(data.window, player_movements, &data);
	mlx_hook(data.window, 17, 0, ft_destroy, &data);

	mlx_loop(data.conx);
}