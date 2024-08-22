/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:54 by yilin             #+#    #+#             */
/*   Updated: 2024/08/22 21:15:42 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** // DISPLAY WINDOW //
 * @brief Initializes the graphics library and creates a new game window.
 * 		  If any step fails, it cleans up and returns FAILURE
 * (1) Initialize the graphics library connection
 * (2) If fail to init => exit program + return (FAILURE)
 * (3) Create a new window with the given width, height, and title
 * 	
 * @return return(SUCCESS) or return (0) 
 */
//// display window ////
/*
Initializes a connection with the graphical system and creates a window. 
If any step fails, it cleans up and returns an error.
 */
int	display_window(t_mlx *data, char *filename, int width, int height)//"so_long" pass as arg
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (exit_program(data), FAILURE);
	// mlx_new_window() ->Create a new window with the specified width, height, and title
	//void	*mlx_new_window(t_xvar *xvar,int size_x,int size_y,char *title)
	data->window = mlx_new_window(data->mlx_ptr, width * BPS, height * BPS, filename);
	// If the window creation fails => clean up and return ERROR(1)
	if (!data->window)
		return (exit_program(data), FAILURE);
	return (SUCCESS);
}

/** // LOAD IMGS //
 * @brief various textures (images) for different objects (walls, floor, player, etc.) in the game.
 * @param i: Initialize a variable i => store imgs dimensions
 * // void	*mlx_xpm_file_to_image(t_xvar *xvar,char *filename, int *width, int *height)
 * 
 * @note data->img[WALL]: an element of the img array => a structure array => store img data.
 * @note data->img[WALL].ptr: ".ptr" stores the memory address of the loaded image
 *       => where mlx_xpm_file_to_image() stores the pointer to the loaded image data.
 * 
 * @return (SUCCESS) or (0)
**/
int	load_imgs(t_mlx *data)
{
	int	i;

	i = 0;
	// Load the image for the wall and store its pointer
	data->img[WALL].ptr = mlx_xpm_file_to_image(data->mlx_ptr, WALL_PATH, &i, &i);
	// Load the image for the floor and store its pointer
	data->img[FLOOR].ptr = mlx_xpm_file_to_image(data->mlx_ptr, FLOOR_PATH, &i, &i);
	// Load the image for the exit (state 1) and store its pointer
	data->img[EXIT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_PATH, &i, &i);
	// Load the image for the exit (state 2) and store its pointer
	data->img[EXIT2].ptr = mlx_xpm_file_to_image(data->mlx_ptr, EXIT2_PATH, &i, &i);
	// Load the image for the coin and store its pointer
	data->img[CAKE].ptr = mlx_xpm_file_to_image(data->mlx_ptr, CAKE_PATH, &i, &i);
	// Load the images for the player (facing downwards) and store their pointers
	data->img[PDOWN].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PDOWN_PATH, &i, &i);
	// TBD: player facing up
	data->img[PUP].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PUP_PATH, &i, &i);
	// TBD: player facing right
	data->img[PRIGHT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PRIGHT_PATH, &i, &i);
	// TBD: player facing left
	data->img[PLEFT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PLEFT_PATH, &i, &i);
	return (SUCCESS);
}

/** // DISPLAY MAP //
 * @brief Draws the entire game map on the window, placing the correct texture at each position based on the map data.
 * @param x 左右=> column (horizontal position)
 * @param y 上下 row (vertical position)
 * (1) Loop through each row(y = vertical) of the map
 * (2) Loop through each column(x = horizontal) of the map
 * (3) print img: //int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
*/
void	init_map(t_mlx *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			//if '1' (WALL) => print wall img
			if (data->map[y][x] == '1')
				print_img(data, data->img[WALL].ptr, x * BPS, y * BPS);
			//if '0' (FLOOR) => print floor img
			if (data->map[y][x] == '0')
				print_img(data, data->img[FLOOR].ptr, x * BPS, y * BPS);
			//if 'P' (PLAYER) => print player img
			if (data->map[y][x] == 'P')
				print_img(data, data->img[PDOWN].ptr, x * BPS, y * BPS);
			//if 'C' (CAKE) => print cake img
			if (data->map[y][x] == 'C')
				print_img(data, data->img[CAKE].ptr, x * BPS, y * BPS);
			//if 'E' (EXIT) => print exit img
			if (data->map[y][x] == 'E')
				print_img(data, data->img[EXIT].ptr, x * BPS, y * BPS);
			//
			else if (data->map[y][x] == 'E' && data->left_cakes == 0)
				print_img(data, data->img[EXIT2].ptr, x * BPS, y * BPS);
		}
	}
}

/** // MOVE N DISPLAY PLAYER //
 * @brief Handles the animation of the player character as it moves, 
 *        updating the display and keeping track of the number of moves.
 * (1) Calculate the player's initial position on the screen
 * (2) Display the player's current image at initial position
 * (3) Synchronize the graphical display
 * (4) Check if the player is blocked from moving => return
 * (5) animate player()
 * (6) Increment and print the move count
 * (7) Disiplay the player's current image at the new positon
 * (8) Synchronize the graphical display again => guarantees that the animation appears smoothly
*/

//Animates the player on the screen, 
//handles movement, and updates the move count.
void	move_n_track_player(t_mlx *data)
{
	int	x;
	int	y;
	int	i;
	
	i = 0;
	x = data->p_x * BPS;
	y = data->p_y * BPS;
	print_img(data, data->img[data->p_dir].ptr, x, y);

	mlx_do_sync(data->mlx_ptr);
	if (is_pos_blocked(data))
		return ;
	animate_player(data, &x, &y, i);
	ft_printf("moves count: %d\n", ++data->moves);
	print_img(data, data->img[data->p_dir].ptr, x, y);
	mlx_do_sync(data->mlx_ptr);
}

/** // run player animation //
 * @brief Performs a smooth transition animation as the player moves from one position to another,
 *        updating the player's sprite and position incrementally.
 * Loop to perform the animation in small steps
 * Adjust the player's position based on the direction they are facing
 * PUP / PRIGHT / PDOWN / PLEFT => moves the object up by 2 pixels(for smoother animation)
 * @note uSleep(milliseconds]) =>create a smooth animation effect
 * 		//suspend execution for a given number of microseconds => slow down an animation => creating a delay between each frame.
 * 
*/
void	animate_player(t_mlx *data, int *x, int *y, int i)
{
	while (i < BPS / 2)
	{
		if (data->p_dir == PUP)
			*y -= 2;
		else if (data->p_dir == PRIGHT)
			*x += 2;
		else if (data->p_dir == PDOWN)
			*y += 2;
		else if (data->p_dir == PLEFT)
			*x -= 2;
		// Display the player's current frame of animation => "walking animation"
		if (i % 1 == 0)//i-> even int => alternate between two frames of an animation
			print_img(data, data->img[data->p_dir].ptr, *x, *y);
		// Display the next frame in the animation sequence
		// else if (i % 2 == 0) //execute a block of code every four iterations
		// 	print_img(data, data->img[data->p_dir + 1].ptr, *x, *y);
		// Display the final frame in the animation sequence
		// else
		// 	print_img(data, data->img[data->p_dir + 2].ptr, *x, *y);
		mlx_do_sync(data->mlx_ptr);
		usleep(12000);
		i++;
	}
}