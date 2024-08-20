/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:51 by yilin             #+#    #+#             */
/*   Updated: 2024/08/20 19:28:05 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// is pos passable ////
/**
 * Checks if the given position is blocked in the specified direction.
 * 
 * @brief '1': represents a wall or some other impassable obstacle in the map.
 * @brief 'E': represents an exit or some other special map feature that might block movement.
 * 
 * @return TRUE(1) if the position is blocked
 * @return FALSE(0) if the position is NOT blocked->passable
 **/

bool is_pos_blocked(t_mlx *data)
{
    // Check if the position in the direction the player is facing is blocked
    if ((data->p_dir == PUP &&
        (data->map[data->p_y - 1][data->p_x] == '1' || data->map[data->p_y - 1][data->p_x] == 'E')) ||
        (data->p_dir == PRIGHT &&
        (data->map[data->p_y][data->p_x + 1] == '1' || data->map[data->p_y][data->p_x + 1] == 'E')) ||
        (data->p_dir == PDOWN &&
        (data->map[data->p_y + 1][data->p_x] == '1' || data->map[data->p_y + 1][data->p_x] == 'E')) ||
        (data->p_dir == PLEFT &&
        (data->map[data->p_y][data->p_x - 1] == '1' || data->map[data->p_y][data->p_x - 1] == 'E')))
    {
        return (TRUE); //return (1) => blocked
    }
    return (FALSE); //return (0) => passable
}

//// is map valid ////
bool is_map_valid(char **map, char *file_name, t_mlx *data)
{
	// Structure to store element counts and the DFS(depth first search) map
	t_check	content;
	
	// If the map is NULL OR the filename doesn't end in ".ber" => print an error and return false.
	if (!map || ft_strcmp(".ber", file_name + ft_strlen(file_name) - 4))
		return (ft_putstr_fd("Wrong file name\n", STDERR_FILENO), FALSE);
	// If the map has less than 3 lines => print an error and return false.
	else if (ft_strslen((const char **)map) <= 2)
		return (ft_putstr_fd("Map too small (less than 3 lines)\n", STDERR_FILENO), FALSE);
	// If the map is not a rectangle, print an error and return false.
	else if (!is_map_rectangle(map))
		return (ft_putstr_fd("Map is not rectangle\n", STDERR_FILENO), FALSE);
	// Initialize the t_checks structure.
	content = (t_check){0, 0, 0, NULL};
	// If the map doesn't have the correct number of valid elements => print an error and return false.
	if (!is_elements_valid(map, &content))
		return (ft_putstr_fd("Elements invalid\n", STDERR_FILENO), FALSE);
	// Store the number of coins in the data structure.
	data->left_collectable = content.count_collectable;
	// If there's no valid path in the map => print an error and return false.
	if (!is_path_valid(map, &content))
		return (ft_putstr_fd("Path Invalid\n", STDERR_FILENO), FALSE);
	return (TRUE);
}

//// is rectangle ////
/**
 * Checks if the the given map is rectangular => all rows (except possibly the last one) have the same width.
 * 
 * @return TRUE(1) if the position is 
 * @return FALSE(0) if the position is not
 **/
bool	is_map_rectangle(char **map)
{
	int		row;
	int		last_row; //last row in the map
	size_t	width;// Expected width of each row (excluding the newline character)

	row = 0;
	last_row = 0;
	// printf("is map rectangle");
	// Set the expected width to the length of the first row, minus 1 for the newline.
	width = ft_strlen(map[0]) - 1;
	// Get the index of the last row in the map.
	row = ft_strslen((const char **)map); // returns the total number of rows => minus 1 to get the index of the last line in the map strs [0][1][2][3]
	// Loop through each row of the map.
	while (map[row])
	{
		// If it's not the last row and the width doesn't match the expected width => return false.
		if (row != last_row && ft_strlen(map[row]) - 1 != width)
			return (FALSE);
		// If it's the last row and its width doesn't match the expected width (including newline), return false.
		else if (row == last_row && ft_strlen(map[row]) != width)
		row++;
	}
	return (TRUE);
}
/*
char *map[] = 
{
    "1111\n",
    "1001\n",
    "1001\n",
    "1111\n",
    NULL
};
*/

//// elements valid ////
bool	is_elements_valid(char **map, t_check *content)
{
	int	y; //Row index variable.
	int	x; //Column index variable.

	y = -1;
	// Iterate through each row in the map.
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			// Increment the count of 'P' (player) elements.
			if (map[y][x] == 'P')
				content->player_count++;
			// Increment the count of 'E' (exit) elements.
			if (map[y][x] == 'E')
				content->exit_count++;
			// Increment the count of 'C' (collectible) elements.
			if (map[y][x] == 'C')
				content->count_collectable++;
			// If the character is not one of the valid ones(1, P, E, C, \n) => return false (invalid map).
			if (map[y][x] != '1' || map[y][x] != 'P' || map[y][x] != 'E' || map[y][x] != 'C' || map[y][x] != '\n')
				return (TRUE);			
		}
	}
	return (FALSE);
}

//// is line valid ////
bool	is_line_valid(char **line, int y, int wall)
{
	int	x;// Column index variable

	x = 0;
	// If the first character of the line is not '1' (a wall)=> return false
	if (line[y][x] != '1')
		return (FALSE);
	// Loop through the line -> check for a wall.
	while (line[y][++x])
	{
		// If a "non-wall character" is found in a wall line => return false
		if (line[y][x] != '1')
			return (FALSE);
		// If the end of the line is reached => return true (valid wall line)
		if (line[y][x + 1] == '\n' || line[y][x + 1] == '\0')
			return (TRUE);
	}
	// Loop through the line -> check NOT a wall.
	while (line[y][++x] && !wall)
	{
		// If a '1' is found and it's not followed by a newline = > skip to the next character.
		if (line[y][x] == '1' && line[y][x + 1] != '\n')
			x++;
		// If a '1' is found and it's followed by a newline => return true (valid non-wall line).
		if (line[y][x] == '1' && line[y][x + 1] == '\n')
			return (TRUE);
		// If a 'C' (collectible) or invalid 'E' (exit) is found => return false.
		if (line[y][x] == 'C' || ((line[y][x] == 'E' && line[y][x + 1] != '~')// right of the exit is not a valid path
		&& (line[y][x] == 'E' && line[y][x - 1] != '~')//left of the exit is not a valid path.
		&& (line[y][x] == 'E' && line[y - 1][x] != '~')//above the exit is not a valid path.
		&& (line[y][x] == 'E' && line[y + 1][x] != '~')))//below the exit is not a valid path.
			return (FALSE);
	}
	return (FALSE);// Return false if the line is invalid.
}

// void	display(char **data)
// {
// 	int i = 0;
// 	while (data[i])
// 	{
// 		printf("%s", data[i]);
// 		i++;
// 	}
// }

//// is path valid ////
bool is_path_valid(char **map, t_check *content)
{
	size_t row; // Row index variable.
	long pos; // Position of the player in the map (x and y coordinates combined).
	size_t n_rows; // Number of rows in the map.
	
	pos = get_xy(map, 'P'); // Get the coordinates of the player.
	content->dfs_map = ft_strsdup(map);// !!RETURNS UNALLOCATED MEMORY CAUSING SEGFAULTS LATER!! Duplicate the map for depth-first search (DFS).
	// display(content->dfs_map);
	n_rows = ft_strslen((const char **)content->dfs_map);// Get the number of rows
	// Perform DFS starting from the player's position to mark reachable '0', 'P', and 'C' elements.
	ft_dfs(content->dfs_map, pos >> 32, pos & 0xFFFFFFFF, "OPC");
	row = 0;
	while (row < n_rows)
	{
		// If it's the first or last line and it's not valid => free the DFS map and return false.
		if ((row == 0 || row == (n_rows - 1)) && !is_line_valid(content->dfs_map, row, TRUE))
		{
			free_strs(content->dfs_map, 1);
			return (TRUE);
		}
		// If it's not the first or last line and it's not valid => free the DFS map and return false.
		else if (row != 0 && row != (n_rows - 1) && !is_line_valid(content->dfs_map, row, FALSE))
		{
			free_strs(content->dfs_map, 1);
			return (TRUE);
		}
		row++;
    }
	// Free the DFS map and return true if the path is valid.
	free_strs(content->dfs_map, 1);
	return (FALSE);
}
// bool	is_path_valid(char **map, t_check *content)
// {
// 	size_t	row; // Row index variable.
// 	long	pos; // Position of the player in the map (x and y coordinates combined).

// 	pos = get_xy(map, 'P');// Get the coordinates of the player.
// 	// Duplicate the map for depth-first search (DFS).
// 	content->dfs_map = ft_strsdup(map);
// 	//starting from the player's position, to explore and mark all reachable locations in the map that contain valid paths ('0'), collectibles ('C'), or the player ('P')
// 	ft_dfs(content->dfs_map, pos >> 32, pos & 0xFFFFFFFF, "OPC");
// 	// Perform DFS starting from the player's position to mark reachable '0', 'P', and 'C' elements.
// 	// Iterate through each line in the DFS map.
// 	row = -1;
//     while (content->dfs_map[++row])
// 	{
// 		// If it's the first or last line and it's not valid => free the DFS map and return false.
// 		if ((row == 0 || row == ft_strslen((const char **)content->dfs_map) - 1)
// 			&& !is_line_valid(content->dfs_map, row, TRUE))
// 			return (free_strs(content->dfs_map, 1), FALSE);
// 		// If it's not the first or last line and it's not valid => free the DFS map and return false.
// 		else if (!(row == 0 || row == ft_strslen((const char **)content->dfs_map) - 1)
// 			&& !is_line_valid(content->dfs_map, row, FALSE))
// 			return (free_strs(content->dfs_map, 1), FALSE);
// 	// Free the DFS map and return true if the path is valid.
// 	return (free_strs(content->dfs_map, 1), TRUE);
// 	}
// }


/*
pos >> 32: This extracts the y coordinate of the player’s position.

If pos is a 64-bit integer containing both x and y coordinates, the y coordinate is typically stored in the higher 32 bits. By right-shifting p by 32 bits (p >> 32), you bring the y coordinate to the lower 32 bits, effectively extracting it.

pos & 0xFFFFFFFF: This extracts the x coordinate of the player’s position.

The bitwise AND operation with 0xFFFFFFFF (which is a 32-bit mask with all bits set to 1) extracts the lower 32 bits of p, which represents the x coordinate.

*/