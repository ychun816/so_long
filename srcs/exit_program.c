/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:57 by yilin             #+#    #+#             */
/*   Updated: 2024/08/18 20:04:22 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_program(t_mlx	*data)
{
	int	i;
	
	// If the passed data is NULL, exit the program immediately.
	if (!data)
		exit(EXIT_FAILURE);//return 0?
	// If the map exists in the data, free the map function.
	if (data)
		free_strs(data->map, TRUE); //char **strs //ft_freetab(data->map, TRUE);
	// Loop through all the images (SPRITES_NB is the number of images).
	i = 0;
	while (i < SPRITES_NB)
	{
		// If an image pointer is not NULL, destroy the image to free up resources.
		if (data->img[i].ptr)
			mlx_destroy_image(data->mlx_ptr, data->img[i].ptr);//int	mlx_destroy_image(t_xvar *xvar, t_img *img)
		i++;	
	}
	// If a window exists => destroy window
	if (data->window)
		mlx_destroy_window(data->mlx_ptr, data->window);//int	mlx_destroy_window(t_xvar *xvar,t_win_list *win)
	// If the connection (display context=> "mlx_ptr") exists => destroy it and free the memory.
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);//int	mlx_destroy_display(t_xvar *xvar)
		free (data->mlx_ptr);// the pointer to the allocated memory
	}	
	//exit && return 0
	exit(EXIT_SUCCESS);
}