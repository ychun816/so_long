/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:28:32 by yilin             #+#    #+#             */
/*   Updated: 2024/08/15 19:15:47 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// ft_arraylen ////
int	ft_arraylen(const char **array)
{
	size_t	i;

	// Check if the array is NULL or empty
	if (!array || !(*array))
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i); 	
}

/// get_xy ////
/**
 * Finds the coordinates (x, y) of the given element in the map.
 *
 * @param map The 2D array representing the map.
 * @param element The element to search for in the map. use 0 to get
 * the end of the map.
 * 
 * A "long integer" is typically 64 bits:
 * "long int" can store two 32-bit integers (representing the x and y coordinates) in one return value.
 * The higher 32 bits store the y coordinate ; the lower 32 bits store the x coordinate. 
 *
 * Initialize x, y to "-1":
 * Error handling: s a clear indicator if something goes wrong before a valid value is found (e.g., if the map is empty). 
 * Edge Cases: If the element isn't found, the loop will complete with y or x remaining at -1, ensuring the function returns -1, signaling an error or invalid coordinates.
 * 
 * @note returns the position of the element if found, otherwise -1.
 * @note x == result & 0xFFFFFFFF
 * @note y == result >> 32
 * long integer allows you to store both x and y in one 64-bit space, where the top 32 bits represent y and the bottom 32 bits represent x
 */
long	get_xy(char** map, char element)
{
	long	x;
	long	y;

	y = -1;
	//if map invalid => return -1
	if (map == NULL)
		return (-1);
	//if map valid => iterate each row(y) => then iterate each column(x)
	while(map[++y])//Starts at map[0]; [y++] starts at map[-1] => wrong behavior	
	{
		x = -1;
		while (map[y][++x])
		{
			// If the element is found => Combine y and x into a single long integer and return it
			if (map[y][x] == element)
				return (y << 32 | x) // "OR" operator combines the bits of y (now in the higher 32 bits) with x (in the lower 32 bits) into a single long integer.
		}
	}
	// If element is 0 => return the position after the last valid element
	if (element == 0)
		return (y << 32 | x);
	return (-1); // If the element is not found => return -1
}


/// print_img ////
/**
 * Print an image to the specified position in the window.
 * uses the MiniLibX library to place an image onto a window at the given coordinates.
 * 
 * @param data Pointer to the struct containing mlx data.
 * @param imgptr Pointer to the image to print.
 * @param x The x-coordinate where the image should be printed.
 * @param y The y-coordinate where the image should be printed.
 * @return The result of mlx_put_image_to_window, typically 0 for success.
 */
//int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img, int x,int y)
int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->window, img_ptr, x, y));	
}

//// ft_arraydup(map) ////
char **ft_arraydup(char **array)
{
	char	**new_array;
	int	i;

	i = 0;
	while (array[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * (i + 1));
	
}

//// ft_dfs ////
/**
 * 
 * Performs a depth-first search on a 2d map, starting from a 
 * given position (i, j).
 * The search is limited to positions specified in 'notwalls''s characters.
 * Visited positions are filled with '~'.
 * 
 * @param map The map to perform the depth-first search on.
 * @param i The starting row index.
 * @param j The starting column index.
 * @param notwalls A string containing characters that are considered 
 * valid positions to visit.
 * 
 * @note Only a valid starting position will fill the paths.
 */
void	ft_dfs(char **map, int y, int x, char *notwalls)
{
	int	rowlen;// Length of each row in the map (number of columns)
	int	n_rows;// Number of rows in the map

	// Get the length of the first row to determine the number of columns
	rowlen = ft_strlen(*map);
	// Get the number of rows in the map
	n_rows = ft_arraylen((const char **)map);
	// Check if: (1)the current position is out of bounds
	// OR (2)the current character is not in the allowed characters
	// OR (3)the current position is already visited (marked as '~')
	//=> return (end this path)
	if (rowlen < 0 || rowlen >= n_rows || x < 0 || x >= rowlen
		|| !ft_strchr(notwalls, map[y][x])
		|| map[y][x] == '~')
	{
		return ;	
	}
	// Mark the current position as visited by setting it to '~'
	map[y][x] = '~';
	// Recursively explore all four possible directions: up, down, right, left
	ft_dfs(map, y - 1, x, notwalls);//UP
	ft_dfs(map, y + 1, x, notwalls);//DOWN
	ft_dfs(map, y, x + 1, notwalls);//RIGHT
	ft_dfs(map, y, x - 1, notwalls);//LEFT
}
