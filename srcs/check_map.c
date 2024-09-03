/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:37:11 by yilin             #+#    #+#             */
/*   Updated: 2024/08/29 15:20:25 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //is map valid
 * @brief Ensure map meets all the criteria: 
 * correct filename , minimum size, rectangular, valid elements, valid path
 * @note Declare structure to store element counts + DFS(depth first search) map
 * (1) If the map is NULL OR the filename not ".ber" => error + false(0)
 * (2) If the map has less than 3 lines => print an error + return false.
 * (3) If the map is not a rectangle => print an error + return false.
 * (4) Initialize the t_checks structure: content = (t_check){0, 0, 0, 0};
 * (5) If map doesn't have correct number of valid elements => error + false
 * (6) Store the number of cakes in the data structure.
 * (7) If there's no valid path in the map => print an error + return false.
 * @note Standard Error Output = 2
 **/
bool	is_map_valid(char **map, char *file_name, t_mlx *data)
{
	t_check	content;

	if (!map || ft_strcmp(".ber", file_name + ft_strlen(file_name) - 4))
		return (ft_putstr_fd("INVALID MAP: Wrong File\n", 2), FALSE);
	else if (ft_arraylen((const char **)map) <= 2)
		return (ft_putstr_fd("INVALID MAP: Less than 3 lines\n", 2), FALSE);
	else if (!is_map_rectangle(map))
		return (ft_putstr_fd("INVALID MAP: Not Rectangular\n", 2), FALSE);
	content = (t_check){0, 0, 0, 0, 0};
	if (!is_elements_valid(map, &content))
		return (ft_putstr_fd("INVALID MAP: Invalid Elements\n", 2), FALSE);
	data->left_cakes = content.count_cakes;
	if (!is_path_valid(map, &content))
		return (ft_putstr_fd("INVALID MAP: Invalid Path\n", 2), FALSE);
	return (TRUE);
}

/** //is map rectangle
 * @brief Checks if the the given map is rectangular 
 * => all rows (except possibly the last one) have the same width.
 * @param row 
 * @param last_rwo
 * @param width Expected width of each row (excluding the newline character)
 * 
 * (1) Set expected width to the length of the first HORIZONAL row(map[0])
 *     => minus 1 to rid '\n'
 * (2) Get the value of the last row in the map,
 * 	 	=> mins 1 to rid '\n' => ft_arraylen()
 * (3) Loop through each row of the map.
 * - If it's NOT the last row && the width doesn't match the expected width 
 * 	=> return false.
 * - If it's last row && its width not match expected width (including '\n') 
 * 	 => return false.
 * @note last_row might not have '\n' in the end
 * @return TRUE(1) if the position is blocked
 * @return FALSE(0) if the position is not blocked
 **/
bool	is_map_rectangle(char **map)
{
	int		row;
	int		last_row;
	size_t	width;

	row = 0;
	last_row = 0;
	width = ft_strlen(map[0]) - 1;
	last_row = ft_arraylen((const char **)map) - 1;
	while (map[row])
	{
		if (row != last_row && (ft_strlen(map[row]) - 1) != width)
			return (FALSE);
		else if (row == last_row && ft_strlen(map[row]) != width)
			return (FALSE);
		row++;
	}
	return (TRUE);
}

/** // is elements valid//
 * //loop_n_check_elements//
 * @brief Check valid characters (P, E, C, 1, 0, '\n')
 * counts the number of P, E, and C characters,
 * ensures the correct number of each (1 for P/E, at least 1 for C)
 * @param y Row index variable
 * @param x Column index variable.
 * (1) Iratate each horizontal row of map
 * => Increment the count of 'P'/ 'E'/ / 'C'
 * => If the character not one of the valid ones(1, P, E, C, \n) 
 * => return false
 * (2) If number of Player / Exit / Cake are wrong => return FALSE
**/
bool	is_elements_valid(char **map, t_check *content)
{
	loop_n_check_elements(map, content);
	if (content->count_player != 1 || content->count_exit != 1 \
		|| content->count_cakes < 1)
		return (FALSE);
	return (TRUE);
}

/** //is path valid//
 * @param row iterate over the rows of the map
 * @param pos Player's position in a single long integer
 * @param n_rows Number of rows in the map.
 * (1) get player pos
 * (2) dup map -> depth-first-search(DFS)
 *  - !!RETURNS UNALLOCATED MEMORY CAUSING SEGFAULTS LATER!!
 * 	- Duplicate the map for depth-first search (DFS).
 * (3) DFS 
 * - mark reachable cells frm player's pos(x + y coordinates combined)
 * - Perform DFS frm player's position to mark reachable '0', 'P', 'C'
 * (4) check each row
 * 	  => If the row is the first or last row
 * 	  => If the row is NEITHER the first nor last row.
 * 
 * @return if it's the first or last line -> invalid 
 * => free the allocated memory for duplicated map + return FALSE
 * @return if it's NOT the first or last line -> valid 
 * => free memory + return TRUE
 * is_line_valid(content->dfs_map, row, TRUE)
 * //TRUE->is a boundary row
 * //FALSE->not a boundary row
*/
bool	is_path_valid(char **map, t_check *content)
{
	long	pos_long;
	t_dfs	yxpos;
	size_t	row;
	size_t	n_rows;

	pos_long = get_xy(map, 'P');
	yxpos = (t_dfs){.y = pos_long >> 32, .x = pos_long & 0xFFFFFFFF};
	content->dfs_map = ft_arraydup(map);
	n_rows = ft_arraylen((const char **)content->dfs_map);
	ft_dfs(content->dfs_map, yxpos, "0PC", content);
	if (!is_valid_after_dfs(content))
		return (free_strs(content->dfs_map, 1), FALSE);
	row = 0;
	while (row < n_rows)
	{
		if ((row == 0 || row == (n_rows - 1)) && \
			!is_line_valid(content->dfs_map, row, TRUE))
			return (free_strs(content->dfs_map, 1), FALSE);
		else if (row != 0 && row != (n_rows - 1) && \
			!is_line_valid(content->dfs_map, row, FALSE))
			return (free_strs(content->dfs_map, 1), FALSE);
		row++;
	}
	return (free_strs(content->dfs_map, 1), TRUE);
}

/*
pos >> 32: 
This extracts the y coordinate of the player’s position.

If pos is a 64-bit integer containing both x and y coordinates, 
the y coordinate is typically stored in the higher 32 bits. 
By right-shifting p by 32 bits (p >> 32), 
you bring the y coordinate to the lower 32 bits, effectively extracting it.

pos & 0xFFFFFFFF: This extracts the x coordinate of the player’s position.

The bitwise AND operation with 0xFFFFFFFF 
(which is a 32-bit mask with all bits set to 1) 
extracts the lower 32 bits of p, which represents the x coordinate.

*/