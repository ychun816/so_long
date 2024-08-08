/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/08/08 19:26:11 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

//handle input
int handle_keyboard(int keyboard, t_mlx *data)
{
	
	//// Get player coordinates (px, py) from the map ////
	data->player_x = get_xy(data->map, 'P') &  0x0000FFFF; TODO:
	data->player_y = get_xy(data->map, 'p') >> 32; TODO:
	////Handle different key events////
	// If the Escape key is pressed => exit_program
	if (keyboard == XK_Escape)
		exit_program(data);
	// If W or Up arrow key is pressed => move player up
	else if (keyboard == XK_w || keyboard == XK_Up)
		move_player(data, PUP);
	// If D or Right arrow key is pressed => move player right
	else if (keyboard == XK_d || keyboard == XK_Right)
		move_player(data, PRIGHT);
	// If S or Down arrow key is pressed => move player down
	else if (keyboard == XK_s || keyboard == XK_Down)
		move_player(data, PDOWN);
	// If A or Left arrow key is pressed => move player left
	else if (keyboard == XK_a || keyboard == XK_Left)
		move_player(data, PLEFT);
    return (0);
}

//move player
void	move_player(t_mlx *data, int direction)
{
	
}

//set_map
//char **map_copy for Flood fill=>algo to run to check if exit point is valid
void	set_map(t_mlx *data, int y, int x)
{
	
}

// structure

// /*structure for img*/
// typedef struct	s_img
// {
// 	void	*ptr;
// 	char	*pixel_ptr;
// 	int	bpp;//Bits per pixel
// 	int	endian;//端序Endianness of the image data "大端和小端（Big endian and Little endian）"
// 	int	pline_len;//Length of a line of pixels in bytes, used for alignment optimization.
// }	t_img;

// /*structure for player*/
// typedef struct	s_player
// {
// 	int	x;
// 	int	y;
// 	int	step_count;
// }	t_player;

// /*structure for mlx commands*/
// typedef struct s_mlx
// {
// 	void	*mlx_ptr;//Connection pointer (e.g., to a graphics library like MiniLibX) => cnx=connection to mlx
// 	void	*window;
// 	t_img	img[SPRITES_NB];//Array of images
// 	char	**map;//2D array => the game map.
// 	int	width;
// 	int	height;
// 	int	player_x;
// 	int	player_y;
// 	int	player_dir;//player's direction
// 	int	collectable_left;//Number of coins left to collect
// 	int	moves;
// }	t_mlx;

// mlx_hook() => set up event handling for a window in the MiniLibX library

//main
int	main(int ac, char **av)
{
	t_mlx	data;
	int	fd;

	//open map file
	fd = open(av[1], O_RDONLY);
	//init data structure: 
	//*mlx_ptr; *window_ptr;  img[SPRITES_NB]; **map; int	width;height;player_x;player_y;player_dir;collectable_left;moves;
	data = (t_mlx){NULL, NULL, {{NULL, NULL, 0, 0, 0}}, get_file(fd), 0, 0, 0, 0, 0, 0, 0};
	//check map & arg  "." to access => data.map = "the width field inside the data structure"
	if (!is_map_valid(data.map, av[1], &data) || ac <= 1)
		return(exit_program(&data), 1);
	//get map dimensions
	data.width = ft_strlen((const char *)data.map[0]) - 1;//to rid of (\n)
	data.height = ft_arraylen((const char **)data.map);
	// data.map[0] -> "11111"  // First row of the map
	// data.map[1] -> "1P0C1"  // Second row of the map
	// data.map[2] -> "11111"  // Third row of the map

	//display window and map
	display_window(&data, "so_long", data.width, data.height);//"so_long" pass as arg
	set_textures(&data);
	display_map(&data);
	//set mlx key & window close event handler
	mlx_hook(data.window, 2, 1L << 0, handle_keyboard, &data);//1L => long int; <<: bitwise op(shift to left)=>specify an "event mask" for a key press event (in this context, it likely refers to a key being pressed)
	mlx_hook(data.window,17, 1L << 17, exit_program, &data);//shifts the number 1 left by 17 positions=>specify an "event mask" for a window close event (like clicking the close button on the window).
	//start the main loop
	mlx_loop(data.mlx_ptr);
	//cleanup and quit, exit program
	exit_program(&data);	
}


/*
EXAMPLE MAINS
int main(void)
{
    void	*mlx_ptr;
	void	*window_ptr;
 
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (MLX_ERROR);// Handle the error.
    // Do some cool graphical stuff here…
	window_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test window");
	if (!window_ptr)
	{
		free(window_ptr);
		return (MLX_ERROR);
	}
	mlx_key_hook(window_ptr, handle_input, NULL);
	// while (1)
	mlx_pixel_put(mlx_ptr, window_ptr, 640/3, 360/3, 0xFFFFFF);
	mlx_loop(mlx_ptr);
    // Clean up before exiting. The Display struct and the xvar struct
    mlx_destroy_display(mlx_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
    return (0);
}
===================
// int main(void)
// {
//     void	*mlx_ptr;
//     void	*win_ptr;

//     mlx_ptr = mlx_init();
//     if (mlx_ptr == NULL)
//         return (MLX_ERROR);
//     win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
//     if (win_ptr == NULL)
//     {
//         free(win_ptr);
//         return (MLX_ERROR);
//     }
//     while (1);
//     mlx_destroy_window(mlx_ptr, win_ptr);
//     mlx_destroy_display(mlx_ptr);
//     free(mlx_ptr);
// }
*/
