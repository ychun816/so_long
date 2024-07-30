/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/07/30 17:54:18 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

//handle input
int handle_input(int key, void *param)
{
     // Handle the input based on the keycode.
     return (0);
}

//move player


//set_map
//char **map_copy for Flood fill=>algo to run to check if exit point is valid


//main
int	main(int ac, char **av)
{
	t_mlx	data;
	int	fd;

	//open map file
	fd = open(av[1], O_RDONLY);
	//init data structure
	data = 
	//check map & arg
	if (is_map_valid(data.map, av[1]) || ac <= 1)
		return(exit_program(&data), 1);
	//get map dimensions

	//display window and map

	//set mlx key & window close event handler

	//start main loop

	//cleanup and exit program
	exit_program();	
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
