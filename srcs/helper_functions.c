/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:28:32 by yilin             #+#    #+#             */
/*   Updated: 2024/08/22 21:24:12 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**ft_arraylen: measure len of array of strs*/
size_t	ft_arraylen(const char **arrays)
{
	size_t	i;

	if (!arrays || !(*arrays))
		return (0);
	i = 0;
	while (arrays[i])
		i++;
	return (i); 	
}

/**ft_arraydup */
char **ft_arraydup(char **strs)
{
	char	**new_strs;
	int	i;

	i = 0;
	while (strs[i])
		i++;
	new_strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_strs)
		return NULL;
	i = 0;
	while (strs[i])
	{
		new_strs[i] = ft_strdup(strs[i]);
		if (!new_strs[i])
		{
			free_strs(new_strs, TRUE);
			return (0);
		}
		i++;
	}
	new_strs[i] = 0;
	return (new_strs);
}

/** //get_xy
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
 * @note x(column) == result & 0xFFFFFFFF
 * @note y(row) == result >> 32
 * @return If element is 0 => return the position after the last valid element
 * @return returns the position of the element if found, otherwise -1.
 * @return long integer allows you to store both x and y in one 64-bit space, where the top 32 bits represent y and the bottom 32 bits represent x
 * "OR" operator combines the bits of y (now in the higher 32 bits) with x (in the lower 32 bits) into a single long integer.
 */
long	get_xy(char** map, char element)
{
	long	x;
	long	y;

	y = -1;
	if (map == NULL)
		return (-1);
	while(map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == element)
				return (y << 32 | x);
		}
	}
	if (element == 0)
		return (y << 32 | x);
	return (-1);
}

/** //print_img
 * Print an image to the specified position in the window.
 * uses the MiniLibX library to place an image onto a window at the given coordinates.
 * 
 * @param data Pointer to the struct containing mlx data.
 * @param img_ptr Pointer to the image to print.
 * @param x The x-coordinate where the image should be printed.
 * @param y The y-coordinate where the image should be printed.
 * @return The result of mlx_put_image_to_window, typically 0 for success.
 * //int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img, int x,int y)
 */
int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->window, img_ptr, x, y));	
}

/** //strsjoin
 * adds a string to a string strs and returns the resulting strs.
 *
 * @param strs The strs to join the string to.
 * @param str The string to be joined to the strs.
 * @param strs_2free 1/TRUE => free strs after concatenation; 0/FALSE otherwise.
 * @param str_2free 1/TRUE => free s1 after concatenation; 0/FALSE otherwise.
 * @return The resulting string strs after joining the string.
 */
char	**ft_strsjoin(char const **strs, char *last_str, int strs_2free, int str_2free)
{
	char **result;
	size_t	strslen;
	int	i;
	
	strslen = ft_arraylen(strs);
	if ( strs == NULL || last_str == NULL)
		return ((char **)strs);
	result = (char **)malloc( (strslen + 2) * sizeof(char *));//+2: (1)space for last str + (2)space for NULL terminator
	if (!result)
		return (NULL);
	// Copy the strings from the original tab to the new strs
	i = -1;
	while (strs[++i])
		result[i] = ft_strdup(strs[i]);//copy each string from the original strs into result
	result[strslen] =  ft_strdup(last_str);// Add the new string to the end of the strs -> add NULL terminator
	result[strslen + 1] = NULL;
	if (strs_2free)//integer flag => indicates if the original strs of str should befreed.
		free_strs((char **)strs, TRUE);
	if (str_2free)//integer flag => indicates if the new string (str) should be freed
		free(last_str);
	return (result);
}

/*FOR TEST || print map*/
void	test_display_map(t_mlx *data)
{
	int i = 0;
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
}

/*FOR TEST 2*/
// int key_press(int keycode, void *param)
// {
//     (void)param;
//     printf("Key pressed: %d\n", keycode);
//     return (0); 
// }