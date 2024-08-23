/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:57 by yilin             #+#    #+#             */
/*   Updated: 2024/08/23 19:39:18 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * (1) If the passed data is NULL => exit the program immediately.
 * (2) If the map exists in the data, free the map function.
 * (3) Loop through all the imgs (SPRITES_NB is the number of images)
 * 		=> If an image pointer is not NULL => destroy the image + free resources
 * 		//int	mlx_destroy_image(t_xvar *xvar, t_img *img)
 * (4) If a window exists => destroy window 
 * 		//int	mlx_destroy_window(t_xvar *xvar,t_win_list *win)
 * (5) If the connection (display context=> "mlx_ptr") exists => destroy it and free the memory.
 *     //int	mlx_destroy_display(t_xvar *xvar)
 * @return exit(EXIT_SUCCESS) + return (SUCCESS/ 0)
*/	

int	exit_program(t_mlx	*data)
{
	int	i;
	
	if (!data)
		exit(EXIT_FAILURE);
	if (data)
		free_strs(data->map, TRUE);
	i = -1;
	while (++i < SPRITES_NB)
	{
		if (data->img[i].ptr)
			mlx_destroy_image(data->mlx_ptr, data->img[i].ptr);
	}
	if (data->window)
		mlx_destroy_window(data->mlx_ptr, data->window);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free (data->mlx_ptr);// the pointer to the allocated memory
	}	
	return (exit(EXIT_SUCCESS), SUCCESS);
}