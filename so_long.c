/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <ahmel-ou@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:52:53 by ahmel-ou          #+#    #+#             */
/*   Updated: 2025/03/31 07:41:53 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(0);
}

void	join_fail(char *join_map, int fd)
{
	free(join_map);
	close(fd);
	error_exit("Error\nMalloc error");
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
			join_fail(join_map, fd);
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

void	get_images(game_t *d, int width, int height)
{
	int	x;
	int	y;

	d->window = mlx_new_window(d->conx, 60 * width, 60 * height, "so_long");
	d->wall = mlx_xpm_file_to_image(d->conx, "./images/w.xpm", &x, &y);
	d->background = mlx_xpm_file_to_image(d->conx, "./images/b.xpm", &x, &y);
	d->collectible = mlx_xpm_file_to_image(d->conx, "./images/c.xpm", &x, &y);
	d->player = mlx_xpm_file_to_image(d->conx, "./images/p.xpm", &x, &y);
	d->exit = mlx_xpm_file_to_image(d->conx, "./images/e.xpm", &x, &y);
	if (d->width < 5 || d->heigth < 5)
		d->holya = mlx_xpm_file_to_image(d->conx, "./images/holya.xpm",
				&d->holya_w, &d->holya_h);
	else if (d->width < 15 || d->heigth < 15)
		d->holya = mlx_xpm_file_to_image(d->conx, "./images/holya_M.xpm",
				&d->holya_w, &d->holya_h);
	else
		d->holya = mlx_xpm_file_to_image(d->conx, "./images/holya_B.xpm",
				&d->holya_w, &d->holya_h);
}

void	load_graphics(game_t *d)
{
	int	height;
	int	width;

	width = ft_strlen(d->map[0]);
	height = 0;
	d->conx = mlx_init();
	if (d->conx == NULL)
	{
		free_map(d->map);
		error_exit("Error\nMlx failure");
	}
	while (d->map[height])
		height++;
	get_images(d, width, height);
	if (!d->window || !d->collectible || !d->background || !d->wall
		|| !d->player || !d->exit || !d->holya)
		ft_destroy(d);
}

void	draw_map(game_t *data)
{
	int	i;
	int	j;

	i = 0;
	mlx_put_image_to_window(data->conx, data->window, data->background, 0, 0);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->conx, data->window, data->wall, j
					* 60, i * 60);
			if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->conx, data->window, data->exit, j
					* 60, i * 60);
			if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->conx, data->window,
					data->collectible, j * 60, i * 60);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->conx, data->window, data->player, data->p_x
		* 60, data->p_y * 60);
}

void	end_game(game_t *data, void *param)
{
	int	loop;

	loop = 0;
	draw_map(data);
	mlx_clear_window(data->conx, data->window);
	mlx_put_image_to_window(data->conx, data->window, data->background, 0, 0);
	mlx_put_image_to_window(data->conx, data->window, data->holya, data->width
		* 30 - (data->holya_w / 2), data->heigth * 30 - (data->holya_h / 2));
	mlx_do_sync(data->conx);
	while (loop++ < 500000000)
		;
	ft_destroy(param);
}

void	update_position(game_t *data, int key)
{
	if (key == W_KEY)
	{
		if (data->map[data->p_y - 1][data->p_x] != '1')
			data->p_y -= 1;
	}
	if (key == A_KEY)
	{
		if (data->map[data->p_y][data->p_x - 1] != '1')
			data->p_x -= 1;
	}
	if (key == S_KEY)
	{
		if (data->map[data->p_y + 1][data->p_x] != '1')
			data->p_y += 1;
	}
	if (key == D_KEY)
	{
		if (data->map[data->p_y][data->p_x + 1] != '1')
			data->p_x += 1;
	}
}

int	player_movements(int key, void *param)
{
	game_t	*data;

	data = (game_t *)param;
	update_position(data, key);
	if (data->map[data->p_y][data->p_x] == 'C')
	{
		data->map[data->p_y][data->p_x] = '0';
		data->count -= 1;
	}
	if (data->map[data->p_y][data->p_x] == 'E' && data->count == 0)
		end_game(data, param);
	if (key == ESC_KEY)
		ft_destroy(param);
	mlx_clear_window(data->conx, data->window);
	draw_map(data);
	return (0);
}

void	player_position(game_t *data)
{
	int	i;
	int	j;

	i = 0;
	data->count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->p_x = j;
				data->p_y = i;
			}
			if (data->map[i][j] == 'C')
			{
				data->count++;
			}
			j++;
		}
		i++;
	}
	data->width = j;
	data->heigth = i;
}

int	ft_destroy(void *param)
{
	game_t	*data;

	data = (game_t *)param;
	free_map(data->map);
	if (data->background != NULL)
		mlx_destroy_image(data->conx, data->background);
	if (data->exit != NULL)
		mlx_destroy_image(data->conx, data->exit);
	if (data->wall != NULL)
		mlx_destroy_image(data->conx, data->wall);
	if (data->player != NULL)
		mlx_destroy_image(data->conx, data->player);
	if (data->collectible != NULL)
		mlx_destroy_image(data->conx, data->collectible);
	if (data->holya != NULL)
		mlx_destroy_image(data->conx, data->holya);
	if (data->window != NULL)
		mlx_destroy_window(data->conx, data->window);
	exit(0);
}

int	main(int argc, char *argv[])
{
	char	**map;
	game_t	data;

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
	player_position(&data);
	load_graphics(&data);
	draw_map(&data);
	mlx_key_hook(data.window, player_movements, &data);
	mlx_hook(data.window, 17, 0, ft_destroy, &data);
	printf("count == %d\n", data.count);
	mlx_loop(data.conx);
}
