/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:28:32 by yilin             #+#    #+#             */
/*   Updated: 2024/09/03 17:54:59 by yilin            ###   ########.fr       */
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
char	**ft_arraydup(char **strs)
{
	char	**new_strs;
	int		i;

	i = 0;
	while (strs[i])
		i++;
	new_strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_strs)
		return (NULL);
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
 * @param map The 2D array representing the map.
 * @param element Player, Exit, Cakes, Villains 
 * @note
 * A "long int" is typically 64 bits:
 * - stores two 32-bit integers (= x & y coordinates) in one return value.
 * - The higher 32 bits store the y coordinate ; 
 * - the lower 32 bits store the x coordinate. 
 *
 * Initialize x, y to "-1":
 * - Error handling:
 * if error before a valid value found (e.g., if the map is empty). 
 * - Edge Cases:
 * If element not found, loop ends with y or x remaining at -1,
 * 
 * @note x(column) == result & 0xFFFFFFFF
 * @note y(row) == result >> 32
 * @return If element is 0 => return the position after the last valid element
 * @return returns the position of the element if found, otherwise -1.
 * @return long int => store both x and y in one 64-bit space, 
 * where the top 32 bits represent y and the bottom 32 bits represent x
 * "OR" operator combines the bits of y (now in the higher 32 bits) 
 * with x (in the lower 32 bits) into a single long integer.
 */
long	get_xy(char **map, char element)
{
	long	x;
	long	y;

	y = -1;
	if (map == NULL)
		return (-1);
	while (map[++y])
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
 * @param data Pointer to the struct containing mlx data.
 * @param img_ptr Pointer to the image to print.
 * @param x The x-coordinate where the image should be printed.
 * @param y The y-coordinate where the image should be printed.
 * @return The result of mlx_put_image_to_window, typically 0 for success.
 */
int	print_img(t_mlx	*data, void *img_ptr, int x, int y)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->window,
			img_ptr, x, y));
}

/** //strsjoin
 * adds a string to a string strs and returns the resulting strs.
 *
 * @param strs The strs to join the string to.
 * @param str The string to be joined to the strs.
 * @param ss 1/TRUE => free strs after concatenation; 0/FALSE otherwise.
 * @param str 1/TRUE => free s1 after concatenation; 0/FALSE otherwise.
 * @note
 * - (strslen + 2): (1)space for last str;(2)space for NULL terminator
 * - if (ss) integer flag => indicates if the og strs of str should be freed.
 * - if (str) integer flag => indicates if the new string (str) should be freed
 * @return The resulting string strs after joining the string.
 * 
 */
char	**ft_strsjoin(char const **strs, char *end_s, int ss_fr, int s_fr)
{
	char	**result;
	size_t	strslen;
	int		i;

	strslen = ft_arraylen(strs);
	if (strs == NULL || end_s == NULL)
		return ((char **)strs);
	result = (char **)malloc((strslen + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	while (strs[++i])
		result[i] = ft_strdup(strs[i]);
	result[strslen] = ft_strdup(end_s);
	result[strslen + 1] = NULL;
	if (ss_fr)
		free_strs((char **)strs, TRUE);
	if (s_fr)
		free(end_s);
	return (result);
}

/*FOR TEST || print map
void	test_display_map(t_mlx *data)
{
	int i = 0;
	while (data->map[i])
	{
		ft_printf("%s", data->map[i]);
		i++;
	}
	ft_printf("\n", data->map[i]);
}
*/

/*// FOR TEST 2 || DFS MAP
void	test_display_dfsmap(char **map)
{
	int i = 0;
	while (map[i])
		printf("%s", map[i++]);
}*/

/*FOR TEST 3
int key_press(int keycode, void *param)
{
    (void)param;
    printf("Key pressed: %d\n", keycode);
    return (0); 
}
*/