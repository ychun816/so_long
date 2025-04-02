/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:54 by yilin             #+#    #+#             */
/*   Updated: 2024/08/27 19:50:31 by yilin            ###   ########.fr       */
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
 * @return return(SUCCESS) / (0) 
 */
int	display_window(t_mlx *data, char *filename, int width, int height)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (exit_program(data), FAILURE);
	if (is_gamewindow_oversize(data, width * BPS, height * BPS))
	{
		ft_putstr_fd("INVALID GAME: Game Window Oversize\n", STDERR_FILENO);
		return (exit_program(data), FAILURE);
	}
	data->window = mlx_new_window(data->mlx_ptr,
			width * BPS, height * BPS, filename);
	if (!data->window)
		return (exit_program(data), FAILURE);
	return (SUCCESS);
}

/** // LOAD IMGS //
 * @param i: Initialize a variable i => store imgs dimensions
 * @note data->img[WALL]: an element of the img array 
 * 		=> a structure array => store img data.
 * @note data->img[WALL].ptr: 
 * 		".ptr" stores the memory address of the loaded image
 *       => mlx_xpm_file_to_image() stores the pointer to the loaded image data.
 * @return (SUCCESS) or (0)
**/
int	load_imgs(t_mlx *data)
{
	int	i;

	i = 0;
	if (!data)
		return (0);
	data->img[WALL].ptr = mlx_xpm_file_to_image(data->mlx_ptr, W_P, &i, &i);
	data->img[FLOOR].ptr = mlx_xpm_file_to_image(data->mlx_ptr, F_P, &i, &i);
	data->img[EXIT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, E_P, &i, &i);
	data->img[EXIT2].ptr = mlx_xpm_file_to_image(data->mlx_ptr, E2_P, &i, &i);
	data->img[CAKE].ptr = mlx_xpm_file_to_image(data->mlx_ptr, C_P, &i, &i);
	data->img[PDOWN].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PDWN_P, &i, &i);
	data->img[PUP].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PUP_P, &i, &i);
	data->img[PRIGHT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PR_P, &i, &i);
	data->img[PLEFT].ptr = mlx_xpm_file_to_image(data->mlx_ptr, PL_P, &i, &i);
	data->img[VILLAIN].ptr = mlx_xpm_file_to_image(data->mlx_ptr, V_P, &i, &i);
	check_imgs_valid(data);
	return (SUCCESS);
}

/** // DISPLAY MAP //
 * @brief Draws the entire game map on the window, 
 * placing the correct texture at each position based on the map data.
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
			if (data->map[y][x] == '1')
				print_img(data, data->img[WALL].ptr, x * BPS, y * BPS);
			if (data->map[y][x] == '0')
				print_img(data, data->img[FLOOR].ptr, x * BPS, y * BPS);
			if (data->map[y][x] == 'P')
				print_img(data, data->img[PDOWN].ptr, x * BPS, y * BPS);
			if (data->map[y][x] == 'C')
				print_img(data, data->img[CAKE].ptr, x * BPS, y * BPS);
			if (data->map[y][x] == 'E')
				print_img(data, data->img[EXIT].ptr, x * BPS, y * BPS);
			if (data->map[y][x] == 'V')
				print_img(data, data->img[VILLAIN].ptr, x * BPS, y * BPS);
			else if (data->map[y][x] == 'E' && data->left_cakes == 0)
				print_img(data, data->img[EXIT2].ptr, x * BPS, y * BPS);
		}
	}
}
