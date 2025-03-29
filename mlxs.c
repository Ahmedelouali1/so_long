// #include "so_long.h"

// typedef struct moves
// {
// 	void	*conx;
// 	void	*window;
// 	void	*img;
// 	int		img_x;
// 	int		img_y;
// }			moves_t;


// int	mouse(int key, void *param)
// {
//     moves_t *data;

//     data = (moves_t *)param;
// 	if (key == W_KEY)
// 		data->img_y -= 20; 
// 	if (key == A_KEY)
// 		data->img_x -= 20; 
// 	if (key == S_KEY)
// 		data->img_y += 20; 
// 	if (key == D_KEY)
// 		data->img_x += 20;
//     mlx_clear_window(data->conx, data->window);
//     mlx_put_image_to_window(data->conx, data->window, data->img, data->img_x, data->img_y);
// }

// int	main(int arc, char *argv[])
// {
// 	moves_t data;
// 	int width;
// 	int height;

//     data.img_x = 900;
//     data.img_y = 600;
// 	data.conx = mlx_init();
// 	data.window = mlx_new_window(data.conx, 1800, 1200, "hmida");
// 	data.img = mlx_xpm_file_to_image(data.conx, "./image.xpm", &width, &height);
// 	mlx_put_image_to_window(data.conx, data.window, data.img, 900, 600);
// 	mlx_key_hook(data.window, mouse, &data);


// 	mlx_loop(data.conx);
// }