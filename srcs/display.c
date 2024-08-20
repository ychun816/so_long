/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:54 by yilin             #+#    #+#             */
/*   Updated: 2024/08/19 20:02:14 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// display window ////
/*
Initializes a connection with the graphical system and creates a window. 
If any step fails, it cleans up and returns an error.
 */
int	display_window(t_mlx *data, char *filename, int width, int height)//"so_long" pass as arg
{
	// mlx_init() -> Initialize the connection to the graphical system
	
	data->mlx_ptr = mlx_init();
	// If the connection fails => clean up and return return ERROR(1)
	if (!data->mlx_ptr)
		return (exit_program(data), ERROR);
	// mlx_new_window() ->Create a new window with the specified width, height, and title
	//void	*mlx_new_window(t_xvar *xvar,int size_x,int size_y,char *title)
	data->window = mlx_new_window(data->mlx_ptr, width * BPS, height * BPS, filename);
	// If the window creation fails => clean up and return ERROR(1)
	if (!data->window)
		return (exit_program(data), ERROR);
	return (SUCCESS);// Return SUCCESS(0) to indicate success
}

//// set texture ////
/**
 * @brief various textures (images) for different objects (walls, floor, player, etc.) in the game.
 * 
 * data->img[WALL]: an element of the img array -> likely a structure array used to store image data.
 * data->img[WALL].ptr: ".ptr" stores the memory address of the loaded image,
 * -> where mlx_xpm_file_to_image stores the pointer to the loaded image data.
 * 
**/
int	load_imgs(t_mlx *data)
{
	int	i;

	i = 0;
	//// void	*mlx_xpm_file_to_image(t_xvar *xvar,char *filename, int *width, int *height)
	// Load the image for the wall and store its pointer
	data->img[WALL].ptr = mlx_xpm_file_to_image(data->mlx_ptr, WALL_PATH, &i, &i);
	// Load the image for the floor and store its pointer
	data->img[FLOOR].ptr = mlx_xpm_file_to_image(data->mlx_ptr, FLOOR_PATH, &i, &i);
	// Load the image for the exit (state 1) and store its pointer
	data->img[EXIT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_PATH, &i, &i);
	// Load the image for the exit (state 2) and store its pointer
	// data->img[EXIT2].ptr = mlx_xpm_file_to_image(data->mlx_ptr, EXIT2_PATH, &i, &i);
	// Load the image for the coin and store its pointer
	data->img[COLLECTABLE].ptr = mlx_xpm_file_to_image(data->mlx_ptr, COLLECTABLE_PATH, &i, &i);
	// Load the images for the player (facing downwards) and store their pointers
	data->img[PUP].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PUP_PATH, &i, &i);
	// TBD: player facing right
	data->img[PDOWN].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PDOWN_PATH, &i, &i);
	// TBD: player facing upwards
	data->img[PRIGHT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PRIGHT_PATH, &i, &i);
	// TBD: player facing left
	data->img[PLEFT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PLEFT_PATH, &i, &i);
	return (SUCCESS);
}

//// display map ////
//Renders the map on the screen based on a 2D array of characters,
//each representing different elements like walls, floor, player, etc.
void	display_map(t_mlx *data)
{
	int	y;
	int	x;
	
	y = -1;
	while (data->map[++y])// Loop through each row of the map
	{
		x = -1;
		while (data->map[y][++x])
		{
			////int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
			//if '1' (WALL) => print wall img
			if (data->map[y][x] == '1')
				print_img(data, data->img[WALL].ptr, x * BPS, y * BPS);
			//if '0' (FLOOR) => print floor img
			if (data->map[y][x] == '0')
				print_img(data, data->img[FLOOR].ptr, x * BPS, y * BPS);
			//if 'P' (PLAYER) => print player img
			if (data->map[y][x] == 'P')
				print_img(data, data->img[PDOWN].ptr, x * BPS, y * BPS);
			//if 'C' (COLLECTABLE) => print collectable img
			if (data->map[y][x] == 'E')
				print_img(data, data->img[EXIT].ptr, x * BPS, y * BPS);
			//if 'E' (EXIT) => print exit img
			if (data->map[y][x] == 'C')
				print_img(data, data->img[COLLECTABLE].ptr, x * BPS, y * BPS);
		}
	}
}

//// animate player ////
//Animates the player on the screen, 
//handles movement, and updates the move count.
void	move_player(t_mlx *data)
{
	int	x;
	int	y;
	int	i;
	// Calculate the player's initial position on the screen
	i = 0;
	x = data->p_x * BPS;
	y = data->p_y * BPS;
	//Display the player's current image at initial position
	print_img(data, data->img[data->p_dir].ptr, x, y);
	// Synchronize the graphical display
	mlx_do_sync(data->mlx_ptr);
	// Check if the player is blocked from moving => return
	if (is_pos_blocked(data))
		return ;
	// TBD: Run the animation for the player movement
	run_player_animation(data, &x, &y, i);
	// Increment and print the move count
	ft_printf("moves count: %d\n", ++data->moves);
	// Display the player's current image at the new position
	print_img(data, data->img[data->p_dir].ptr, x, y);
	// Synchronize the graphical display again => guarantees that the animation appears smoothly
	mlx_do_sync(data->mlx_ptr);
}

// //// TBD ////
// //// run player animation ////
// // Handles the frame-by-frame animation of the player's movement in small steps.
void	run_player_animation(t_mlx *data, int *x, int *y, int i)
{
	// Loop to perform the animation in small steps
	while (i < BPS / 2)
	{
		// Adjust the player's position based on the direction they are facing
		if (data->p_dir == PUP) //UP => moves the object up by 2 pixels(for smoother animation)
			*y -= 2;
		else if (data->p_dir == PRIGHT) //RIGHT
			*x += 2;
		else if (data->p_dir == PDOWN) //DOWN
			*y += 2;
		else if (data->p_dir == PLEFT) //LEFT
			*x -= 2;
		// Display the player's current frame of animation => "walking animation"
		if (i % 2 == 0)//i-> even int => alternate between two frames of an animation
			print_img(data, data->img[data->p_dir].ptr, *x, *y);//PDOWN (standing position)
		// Display the next frame in the animation sequence
		else if ((i - 1) % 4 == 0) //execute a block of code every four iterations
			print_img(data, data->img[data->p_dir + 1].ptr, *x, *y);//PDOWN1(left foot walking position)
		// Display the final frame in the animation sequence
		else
			print_img(data, data->img[data->p_dir + 2].ptr, *x, *y);//PDOWN2(right foot walking position)
		// Synchronize the graphical display
		mlx_do_sync(data->mlx_ptr);
		// uSleep for 10 milliseconds to create a smooth animation effect
		//suspend execution for a given number of microseconds => slow down an animation => creating a delay between each frame.
		usleep(10000);
		i++;
	}
}