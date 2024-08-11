/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/08/11 20:55:44 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

////HANDLE KEYBOARD////
int handle_keyboard(int keyboard, t_mlx *data)
{
	//// Get player coordinates (px, py) from the map ////
	
	//extracts the x-coordinate from the lower 16 bits of the 64-bit value
	//x-coordinate and the upper 48 bits are irrelevant for x-coordinate extraction, 
	//the mask 0x0000FFFF will effectively zero out all but the lower 16 bits, giving you just the x-coordinate.
	data->p_x = (data->map, 'P') &  0x0000FFFF;
	//extracts the y-coordinate from the upper 32 bits of the 64-bit value.
	//Shifting the bits of the value returned by get_xy(data->map, 'p') by 32 positions to the right 
	//moves the upper 32 bits into the lower 32-bit position, effectively extracting the y-coordinate if it’s stored in the upper 32 bits of the 64-bit value.
	data->p_y = get_xy(data->map, 'p') >> 32;

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

////MOVE PLAYER////
void	move_player(t_mlx *data, int direction)
{
	// Set player's direction
	data->p_dir = direction;
	//// Check if the player can move in the given direction////
	// If moving UP and not blocked => Update map for moving up
	if (data->p_dir == PUP && !is_blocked(data))
		update_pos_map(data, -1, 0);
	// If moving RIGHT and not blocked => Update map for moving right
	else if (data->p_dir == PRIGHT && !is_blocked(data))
		update_pos_map(data, 0, 1);
	// If moving DOWN and not blocked => Update map for moving down
	else if (data->p_dir == PDOWN && !is_blocked(data))
		update_pos_map(data, 1, 0);
	// If moving LEFT and not blocked => Update map for moving left => // Animate the player's movement
	else if (data->p_dir == PLEFT && !is_blocked(data))
		update_pos_map(data, 0, -1);
}

///UPDATE POS MAP////
//char **map_copy for Flood fill=>algo to run to check if exit point is valid
void	update_pos_map(t_mlx *data, int y, int x)
{
	long	exit;

	//// Check if the player is moving to a position with a collectable////
	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'C')
	{
		// Print a message : "cllectable being collected"
		ft_printf("collectable collected!");
		// Decrease the number of coins left to collect
		data->left_collectable--;
	}
	
	////Get the coordinates of the exit ('E') on the map////
	exit = get_xy(data->map, 'E');

	//// If all collectable have been collected and the exit exists////
	if (data->left_collectable == 0 && exit != -1)
	{
		// Change the exit from 'E' to 'o' (open exit)
		//exit >> 32: This extracts the y coordinate (row) of the exit by shifting the bits of exit 32 positions to the right.
		//exit & 0xFFFFFFFF:"&":"AND" => extracts the x coordinate (column) by masking out the upper 32 bits, leaving only the lower 32 bits.
		data->map[exit >> 32][exit & 0xFFFFFFFF] = 'o';
		//print img
		// Calculate the x-coordinate in pixels by extracting the lower 32 bits of 'exit'
            // (which represent the x-coordinate in map units) and multiplying by BPS (block pixel size) =》block coordinates to pixel coordinates.
		// Calculate the y-coordinate in pixels by shifting 'exit' 32 bits to the right
            // (which gives the y-coordinate in map units) and multiplying by BPS (block pixel size) =》block coordinates to pixel coordinates.
		print_img(data, data->img[EXIT1].ptr , (exit & 0xFFFFFFFF)* BPS, (exit >> 32) * BPS);
		// Synchronize the display with the window (update the graphics)
		mlx_do_sync(data->mlx_ptr);
	}
	// If the player reaches the open exit ('o')
	else if (data->map[(data->p_y) + y][(data->p_x) + x] == 'o')
	{
		//print message
		ft_printf("YOU WON!!!!\n", data->moves);
		//exit program
		exit_program(data);
	}
	// Update the player's position on the map to the new location
	data->map[(data->p_y) + y][(data->p_x) + x] = 'P';
	// Clear the old position of the player on the map
	//NOTE! if dont clear old pos => both the new and old positions marked as the player’s position => wrong logic!
	data->map[data->p_y][data->p_x] = '0';
}

// mlx_hook() => set up event handling for a window in the MiniLibX library

////MAIN////
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
