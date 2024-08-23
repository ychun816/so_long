/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/08/23 22:18:58 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //HANDLE KEYBOARD//
 * @brief processes user input, triggers actions such as moving the player in a specified direction or quitting the game.
 * @param x => extracts the x-coordinate from the lower 16 bits of the 64-bit value
 * x-coordinate and the upper 48 bits are irrelevant for x-coordinate extraction, 
 * the mask 0x0000FFFF will effectively zero out all but the lower 16 bits, giving just the x-coordinate.
 * @param y => extracts the y-coordinate from the upper 32 bits of the 64-bit value.
 * Shifting the bits of the value returned by get_xy(data->map, 'p') by 32 positions to the right 
 * moves the upper 32 bits into the lower 32-bit position => effectively extracting the y-coordinate if it’s stored in the upper 32 bits of the 64-bit value.
 * @return Function returns 0, as required by mlx_hook
 * @note mlx_hook() => set up event handling for a window in the MiniLibX library
 */
int	handle_keypress(int keyboard, t_mlx *data)
{
	// Get player's current x and y positions
	data->p_y = get_xy(data->map, 'P') >> 32;
	data->p_x = get_xy(data->map, 'P') & 0x0000FFFF;
	// If the Escape key is pressed => exit_program
	if (keyboard == XK_Escape)
		exit_program(data);
	// If W or Up arrow key is pressed => move player up
	else if (keyboard == XK_w || keyboard == XK_Up)
		check_n_move_player(data, PUP);
	// If D or Right arrow key is pressed => move player right
	else if (keyboard == XK_d || keyboard == XK_Right)
		check_n_move_player(data, PRIGHT);
	// If S or Down arrow key is pressed => move player down
	else if (keyboard == XK_s || keyboard == XK_Down)
		check_n_move_player(data, PDOWN);
	// If A or Left arrow key is pressed => move player left
	else if (keyboard == XK_a || keyboard == XK_Left)
		check_n_move_player(data, PLEFT);
    return (SUCCESS);
}

/** //CHECK N MOVE PLAYER//
 * @brief moves the player on the game map based on the direction input received from handle_keypress()
 *        whether the movement is blocked (e.g., by a wall or obstacle), updates the player's position accordingly.
 *  If moving UP and not blocked => Update map for moving up
 * 	If moving DOWN and not blocked => Update map for moving down
 * 	If moving RIGHT and not blocked => Update map for moving right
 * 	If moving LEFT and not blocked => Update map for moving left
 */
void	check_n_move_player(t_mlx *data, int pos)
{
	int	p_prevy;
	int	p_prevx;

	p_prevy = data->p_y;
	p_prevx = data->p_x;
	data->p_dir = pos;
	if (data->p_dir == PUP && !is_pos_blocked(data))
		update_map(data, -1, 0);
	else if (data->p_dir == PDOWN && !is_pos_blocked(data))
		update_map(data, 1, 0);
	else if (data->p_dir == PRIGHT && !is_pos_blocked(data))
		update_map(data, 0, 1);
	else if (data->p_dir == PLEFT && !is_pos_blocked(data))
		update_map(data, 0, -1);
	// else if (data->map[data->p_prevy][data->p_prevx] == '0')
	// print_img(data, data->img[FLOOR].ptr, p_prevx * BPS, p_prevy * BPS);
	move_n_track_player(data);
}

/** //UPDATEMAP//
 * @brief updates the game map after the player moves(show player's new position)
 * handles events: collecting coins / opening the exit when all coins are collected/ check win conditions (i.e., reaching the exit after collecting all coins)
 * @param x coordinates => exit & 0xFFFFFFFF => extracts the x coordinate (column) by masking out the upper 32 bits => leaving only the lower 32 bits.
 * @param y coordinates => exit >> 32: This extracts the y coordinate (row) of the exit by shifting the bits of exit 32 positions to the right.
 * @param x print img => Calculate the x-coordinate in pixels[BLOCK to PIXEL coordinates] => extract the lower 32 bits of 'exit' (=the x-coordinate in map units) + multiple by BPS (block pixel size)
 * @param y print img => Calculate the y-coordinate in pixels [BLOCK to PIXEL coordinates] => 
 * 
 * @note (1) Update player's new position on the map / (2)Clear the previous position of the player
 * @note If dont clear old pos => both the new and old positions marked as the player’s position => wrong logic!
 */
void	update_map(t_mlx *data, int y, int x)
{
	long	exit;

	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'V')
	{
		ft_printf("💀💀 AHHH U DEAD!!💀💀\n");
		exit_program(data);
	}
	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'C')
	{
		data->left_cakes--;
		ft_printf("CAKE COLLECTED 🍰 %d CAKES LEFT!\n", data->left_cakes);
		//printf("after left_cakes: %d\n", data->left_cakes);
	}
	exit = get_xy(data->map, 'E');
	if (data->left_cakes == 0)//exit_open // && exit != -1
	{
		data->map[exit >> 32][exit & 0xFFFFFFFF] = 'E';
		print_img(data, data->img[EXIT2].ptr, (exit & 0xFFFFFFFF) * BPS, (exit >> 32) * BPS);
		mlx_do_sync(data->mlx_ptr);
	}
	if (data->left_cakes == 0 && data->map[(data->p_y) + y][(data->p_x) + x] == 'E')//data->left_cakes == 0 && (data->p_y) + y][(data->p_x) + x] == 'E'  
	{
		ft_printf("🎖️ YOU WON!!🎖️ You ate all the cakes in %d moves!\n", data->moves);
		exit_program(data);
	}
	data->map[(data->p_y) + y][(data->p_x) + x] = 'P';
	data->map[data->p_y][data->p_x] = '0';
	// if (data->map[data->p_y][data->p_x] == '0')
	print_img(data, data->img[FLOOR].ptr, data->p_x * BPS, data->p_y * BPS);
	// data->p_y += y;
	// data->p_x += x;
}
	// static int i;
	
	// if (data->p_y + y < 0 || data->p_y + y >= data->height ||  data->p_x + x < 0 || data->p_x + x >= data->width) 
	// {
    //     ft_printf("Out of bounds: new_y=%d, new_x=%d\n", data->p_y + y, data->p_x + x);
    //     return; // Exit the function to prevent out-of-bounds access
	// }
	// printf("TEST %i", i);
	// printf("data->left cakes ---> %i\n", data->left_cakes);
	// test_display_map(data);
	// printf("\n\n");
	// printf("data->p_y ---> %i  y ---> %i\ndata->p_x ---> %i  x ---> %i", data->p_y, y, data->p_x, x);
	// printf("\n\n");
	// data->map[(data->p_y) + y][(data->p_x) + x] = 'P';
	// data->map[data->p_y][data->p_x] = '0';
	// exit = get_xy(data->map, 'E');
	// printf("TEST %i", i);
	// printf("data->left cakes ---> %i\n", data->left_cakes);
	// test_display_map(data);
	// printf("\n\n");
	// printf("data->p_y ---> %i  y ---> %i\ndata->p_x ---> %i  x ---> %i", data->p_y, y, data->p_x, x);
	// printf("\n\n");

//read_n_set_map
/**
 * Declare a result strs (result) to store the lines and a string (line) for the current line
 * (1) If the file descriptor (fd) is invalid => return NULL
 * (2) Read the first line from the file (get next line) -> If reading the first line fails (no content) => return NULL
 * (3) Allocate memory for 2 pointers to store: (1)pointer to one line + (2)pointer to a NULL terminator
 * (4) If memory allocation fails => return NULL
 * (5) Read first line from the file.
 * (6) Indicate the end of the strs. -> result[1] = NULL;
 * (7) Loop until all lines are read from the file 
 *     => Read the next line from the file
 * 	   => Append the line to the result strs using ft_strsjoin -> free both result and line as needed
 * 
 */
char	**read_n_set_map(int fd)
{
	char	**result;
	char	*line;

	if (fd < 0)//|| fd != -1
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * 2); 
	if (!result)
		return (NULL);
	result[0] = line;
	result[1] = NULL;
	while (line)
	{
		line = get_next_line(fd);
		result = ft_strsjoin((char const**)result, line, TRUE, TRUE);
		if (*result == NULL)
			break ;
	}
	return (result);
}

/** //MAIN//
 * (1) open the map file
 * (2) declare n initialize the data structure:
 *     *mlx_ptr; *window_ptr;  img[SPRITES_NB]; **map; int	width;height;player_x;player_y;player_dir;collectable_left;moves;
 * (3) Check if the map is valid && if a file was provided as argument => exit program if invalid
 * (4) Get map dimensions => measure the map's width and height
 * @note ft_strlen: measure length of a single row (width)
 * @note ft_arraylen: measure the number of rows (height) => operates on an array of strings (a 2D array) and returns the number of rows (height) in that array.
 * (5) display window() => load_imgs() => display_map()
 * (6) Set key press hook //mlx_hook(data.window, key_press, NULL)//
 * @note mlx_hook(data.window, 2, 1L << 0, handle_keypress, &data):
 *       1L: long int; <<: bitwise op(shift to left)
 * 		=>Specify an "event mask" for a key press event => refers to a key being pressed
 * (7) Set window close hook
 * @note mlx_hook(data.window,17, 1L << 17, exit_program, &data):
 *       Shifts the number 1 left by 17 positions 
 * 		=>Specify an "event mask" for a window close event => like clicking the close button on the window
 * (8) Start the event loop
 * (9) Exit program

 * initializes game
 * load the map
 * check if the map is valid
 * sets up the game window and textures
 * enters the main event loop
 */
int	main(int ac, char **av)
{
	t_mlx	data;
	int	fd;

	fd = open(av[1], O_RDONLY);
	data = (t_mlx){NULL, NULL, {{NULL, NULL, 0, 0, 0}}, read_n_set_map(fd), 0, 0, 0, 0, 0, 0, 0, 0, 0};
	// test_display_map(&data); //debug
	if (!is_map_valid(data.map, av[1], &data) || ac <= 1)
		return(exit_program(&data), FAILURE);
	// test_display_map(&data); //debug
	data.width = ft_strlen((const char *)data.map[0]) - 1;//remove '\n'
	data.height = ft_arraylen((const char **)data.map);
	display_window(&data, "so_long", data.width, data.height);//display window and map//"so_long" pass as arg
	load_imgs(&data);
	init_map(&data);
	mlx_hook(data.window, 2, 1L << 0, handle_keypress, &data);// Set keypress hook 
	mlx_hook(data.window,17, 1L << 17, exit_program, &data);
	mlx_loop(data.mlx_ptr);	// Start the event loop
	exit_program(&data);
	return (SUCCESS);	
}
