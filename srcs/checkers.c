/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:51 by yilin             #+#    #+#             */
/*   Updated: 2024/08/23 22:55:53 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //is pos blocked
 * Checks if the given position is blocked in the specified direction.
 * 
 * @brief '1': represents a wall or some other impassable obstacle in the map.
 * @brief 'E': represents an exit or some other special map feature that might block movement.
 * 
 * @return TRUE(1) if the position is blocked
 * @return FALSE(0) if the position is NOT blocked->passable
 **/
bool	is_pos_blocked(t_mlx *data)
{
	if (data->p_dir == PUP && (data->map[data->p_y - 1][data->p_x] == '1'
		|| (data->map[data->p_y - 1][data->p_x] == 'E' && data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PRIGHT && (data->map[data->p_y][data->p_x + 1] == '1'
		|| (data->map[data->p_y][data->p_x + 1] == 'E' && data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PDOWN && (data->map[data->p_y + 1][data->p_x] == '1'
		|| (data->map[data->p_y + 1][data->p_x] == 'E' && data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PLEFT && (data->map[data->p_y][data->p_x - 1] == '1'
		|| (data->map[data->p_y][data->p_x - 1] == 'E'  && data->left_cakes != 0)))
		return (TRUE);
	return (FALSE);
}

/** //is map valid
 * @brief Ensure map meets all the criteria: correct filename extension, minimum size, rectangular shape, valid elements, and a valid path.
 * 
 * @note Declare structure to store element counts and the DFS(depth first search) map
 * (1) If the map is NULL OR the filename doesn't end in ".ber" => print an error + return false(0)
 * (2) If the map has less than 3 lines => print an error + return false.
 * (3) If the map is not a rectangle => print an error + return false.
 * (4) Initialize the t_checks structure: content = (t_check){0, 0, 0, NULL};
 * (5) If map doesn't have the correct number of valid elements => print an error + return false.
 * (6) Store the number of cakes in the data structure.
 * (7) If there's no valid path in the map => print an error + return false.
 **/
bool is_map_valid(char **map, char *file_name, t_mlx *data)
{
	t_check	content;

	if (!map || ft_strcmp(".ber", file_name + ft_strlen(file_name) - 4))
		return (ft_putstr_fd("Wrong file name\n", STDERR_FILENO), FALSE);
	else if (ft_arraylen((const char **)map) <= 2)
		return (ft_putstr_fd("Map too small (less than 3 lines)\n", STDERR_FILENO), FALSE);
	else if (!is_map_rectangle(map))
		return (ft_putstr_fd("Map is not rectangular\n", STDERR_FILENO), FALSE);
	content = (t_check){0, 0, 0, 0, NULL};
	if (!is_elements_valid(map, &content))
		return (ft_putstr_fd("Elements invalid\n", STDERR_FILENO), FALSE);
	data->left_cakes = content.count_cakes;
	if (!is_path_valid(map, &content))
		return (ft_putstr_fd("Path Invalid\n", STDERR_FILENO), FALSE);
	return (TRUE);
}
/** //is map rectangle
 * @brief Checks if the the given map is rectangular => all rows (except possibly the last one) have the same width.
 * @param row 
 * @param last_rwo
 * @param width Expected width of each row (excluding the newline character)
 * 
 * (1) Set the expected width to the length of the first HORIZONAL row(map[0]), minus 1 to rid '\n'
 * (2) Get the value of the last row in the map, mins 1 to rid '\n' => ft_arraylen()
 * (3) Loop through each row of the map.
 * 	   => If it's NOT the last row && the width doesn't match the expected width => return false.
 * 	   => If it's the last row && its width doesn't match the expected width (including newline) => return false.
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
			return (FALSE);//0
		else if (row == last_row && ft_strlen(map[row]) != width)
			return (FALSE);//0
		row++;
	}
	return (TRUE);//1
}

/** // is elements valid
 * @brief Check if the map contains valid characters (P, E, C, 1, 0, '\n')
 * counts the number of P, E, and C characters, ensures the correct number of each (1 for P and E, at least 1 for C).
 * @param y Row index variable
 * @param x Column index variable.
 * (1) Iratate each horizontal row of map
 *     => Increment the count of 'P' (player) elements / 'E' (exit) elements/ / 'C' (collectible) elements
 * 	   =>If the character is not one of the valid ones(1, P, E, C, \n) => return false (invalid map).
 * (2) If number of Player / Exit / Cake are wrong => return FALSE
**/
bool	is_elements_valid(char **map, t_check *content)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
				content->count_player++;
			if (map[y][x] == 'E')
				content->count_exit++;
			if (map[y][x] == 'C')
				content->count_cakes++;
			if (map[y][x] == 'V')
				content->count_villains++;
			if (map[y][x] != 'V' && map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'P'
				&& map[y][x] != 'E' && map[y][x] != 'C' && map[y][x] != '\n')
				return (FALSE);//(0)
		}
	}
	if (content->count_player != 1 || content->count_exit != 1 || content->count_cakes < 1)
		return (FALSE);//(0)
	return (TRUE);//(1)
}

/** //is line valid
 * @brief Check if a specific line in the map is properly structured, , ensuring that walls are properly formed depending on whether it is a boundary line or an internal line.
 * (1) If the first character of the line is not '1' (a wall)=> return false
 * (2) If(wall) -> Loop through the line and check for wall validity
 * 	  => If a "non-wall character" is found in a wall line => return false
 * 	  => If the end of the line is reached => return true (valid wall line)
 * (3) else (not wall) -> Loop through the line
 *    => If find '1' && it's not followed by a '\n' OR end-of-line => skip to the next character.
 * 	  => If invalid if 'C' OR an invalid 'E' is found.
 * @return false if the line is invalid
 */
bool	is_line_valid(char **line, int y, int wall)
{
	int	x;

	x = 0;
	if (line[y][x] != '1')
		return (FALSE);//0
	while (line[y][++x] && wall)
	{
		if (line[y][x] != '1')
			return (FALSE);//0
		if (line[y][x + 1] == '\n' || line[y][x + 1] == '\0')//last pos
			return (TRUE);//1
	}
	while (line[y][++x] && !wall)
	{
		if (line[y][x] == '1' && line[y][x + 1] != '\n')
			x++;
		if (line[y][x] == '1' && line[y][x + 1] == '\n')
			return (TRUE);//1
		if (line[y][x] == 'C'
			|| ((line[y][x] == 'E' && line[y][x + 1] != '~')
			&& (line[y][x] == 'E' && line[y][x - 1] != '~')
			&& (line[y][x] == 'E' && line[y - 1][x] != '~')
			&& (line[y][x] == 'E' && line[y + 1][x] != '~')))
			return (FALSE);//0
	}
	return (FALSE);//0
}

/** //is path valid
 * @param row Index variable for iterating over the rows of the map
 * @param pos Player's position encoded in a single long integer
 * @param n_rows Number of rows in the map.
 * (1) get player pos
 * (2) dup map -> depth-first-search(DFS)
 *    // !!RETURNS UNALLOCATED MEMORY CAUSING SEGFAULTS LATER!! Duplicate the map for depth-first search (DFS).
 * (3) DFS -> mark reachable cells starting from the player's position(x and y coordinates combined)
 * 	  // Perform DFS starting from the player's position to mark reachable '0', 'P', and 'C' elements.
 * (4) check each row
 * 	  => If the row is the first or last row
 * 	  => If the row is NEITHER the first nor last row.
 * 
 * @return if it's the first or last line -> invalid => free the allocated memory for the duplicated map + returns FALSE
 * @return if it's NOT the first or last line -> valid => free memory + return TRUE
 * 
*/

bool is_path_valid(char **map, t_check *content)
{
	size_t	row;
	long	pos;
	size_t	n_rows;

	pos = get_xy(map, 'P');
	content->dfs_map = ft_arraydup(map);
	n_rows = ft_arraylen((const char **)content->dfs_map);
	ft_dfs(content->dfs_map, pos >> 32, pos & 0xFFFFFFFF, "0PCV", content);
	// test_display_dfsmap(content->dfs_map);//DEBUG
	if (!is_valid_after_dfs(content))
		return (free_strs(content->dfs_map, 1), FALSE);
	row = 0;
	while (row < n_rows)
	{
		if ((row == 0 || row == (n_rows - 1)) && !is_line_valid(content->dfs_map, row, TRUE))//TRUE->is a boundary row
			return (free_strs(content->dfs_map, 1), FALSE);
		else if (row != 0 && row != (n_rows - 1) && !is_line_valid(content->dfs_map, row, FALSE))//FALSE->not a boundary row
			return (free_strs(content->dfs_map, 1), FALSE);
		row++;
    }
	return (free_strs(content->dfs_map, 1), TRUE);
}
/*
pos >> 32: This extracts the y coordinate of the player’s position.

If pos is a 64-bit integer containing both x and y coordinates, the y coordinate is typically stored in the higher 32 bits. By right-shifting p by 32 bits (p >> 32), you bring the y coordinate to the lower 32 bits, effectively extracting it.

pos & 0xFFFFFFFF: This extracts the x coordinate of the player’s position.

The bitwise AND operation with 0xFFFFFFFF (which is a 32-bit mask with all bits set to 1) extracts the lower 32 bits of p, which represents the x coordinate.

*/