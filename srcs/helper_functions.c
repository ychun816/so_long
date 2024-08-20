/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:28:32 by yilin             #+#    #+#             */
/*   Updated: 2024/08/19 19:36:10 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// ft_strslen ////
int	ft_strslen(const char **strs)
{
	size_t	i;

	// Check if the strs is NULL or empty
	if (!strs || !(*strs))
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i); 	
}

//// ft_strsdup(map) ////
char **ft_strsdup(char **strs)
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
				return (y << 32 | x); //"OR" operator combines the bits of y (now in the higher 32 bits) with x (in the lower 32 bits) into a single long integer.
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
 * @param img_ptr Pointer to the image to print.
 * @param x The x-coordinate where the image should be printed.
 * @param y The y-coordinate where the image should be printed.
 * @return The result of mlx_put_image_to_window, typically 0 for success.
 */
//int	mlx_put_image_to_window(t_xvar *xvar,t_win_list *win,t_img *img, int x,int y)
int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->window, img_ptr, x, y));	
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
	n_rows = ft_strslen((const char **)map);
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

//  TODO: TODO: TODO: void	check_after_dfs()
//  {
	
//  }


///strsjoin///
/**
 * adds a string to a string strs and returns the resulting strs.
 *
 * @param strs The strs to join the string to.
 * @param str The string to be joined to the strs.
 * @param free_strs 1/TRUE => free strs after concatenation; 0/FALSE otherwise.
 * @param free_str 1/TRUE => free s1 after concatenation; 0/FALSE otherwise.
 * @return The resulting string strs after joining the string.
 */
char	**ft_strsjoin(char const **strs, char *last_str, int strs_2free, int str_2free)
{
	char **result;
	size_t	strslen;
	int	i;
	
	strslen = ft_strslen(strs);
	// If either the input strs or str is NULL => return the original strs -> can do no join
	if ( strs == NULL || last_str == NULL)
		return ((char **)strs);
	//malloc place
	result = (char **)malloc( (strslen + 2) * sizeof(char *));//+2: (1)space for last str + (2)space for NULL terminator
	if (!result)
		return (NULL);
	// Copy the strings from the original tab to the new strs
	i = -1;
	while (strs[++i])
		result[i] = ft_strdup(strs[i]);//copy each string from the original strs into result
	// Add the new string to the end of the strs -> add NULL terminator
	result[strslen] =  ft_strdup(last_str);
	result[strslen + 1] = NULL;
	//free strs
	if (strs_2free)//integer flag => indicates if the o riginal strs of str should befreed.
		free_strs((char **)strs, TRUE);
	//free str
	if (str_2free)//integer flag => indicates if the new string (str) should be freed
		free(last_str);
	return (result);
}

/*ref
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*join_str));
	if (!join_str)
		return (NULL);
	while (s1[i])
	{
		join_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join_str[i + j] = s2[j];
		j++;
	}
	join_str[i + j] = '\0';
	return (join_str);
}*/