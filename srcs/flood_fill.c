/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:08:01 by yilin             #+#    #+#             */
/*   Updated: 2024/08/20 19:10:18 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// flood_fill ////
/**
 * 
 * Performs a depth-first search on a 2d map, starting from a 
 * given position (y, x).
 * The search is limited to positions specified in 'notwalls''s characters.
 * Visited positions are filled with '~'.
 * 
 * @param map The map to perform the depth-first search on.
 * @param y The starting row index.
 * @param x The star
 * @param notwalls A string containing characters that are considered 
 * valid positions to visit.
 * 
 * @note Only a valid starting position will fill the paths.
 */
void	flood_fill(char **map, int y, int x, char *notwalls, t_check *content)
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
	if (y < 0 || y >= n_rows || x < 0 || x >= rowlen
        || !ft_strchr(notwalls, map[y][x])
        || map[y][x] == '~')
    {
        return ;
    }
	/*OG
	if (rowlen < 0 || rowlen >= n_rows || x < 0 || x >= rowlen
		|| !ft_strchr(notwalls, map[y][x])
		|| map[y][x] == '~')
	{
		return ;
	}*/
	// Mark the current position as visited by setting it to '~'
	map[y][x] = '~';
	
	// If we encounter a collectible, decrement the collectible counter
    if (map[y][x] == 'C')
		content->count_collectable--;
	
	// Recursively explore all four possible directions: up, down, right, left
	flood_fill(map, y - 1, x, notwalls, content);//UP
	flood_fill(map, y + 1, x, notwalls, content);//DOWN
	flood_fill(map, y, x + 1, notwalls, content);//RIGHT
	flood_fill(map, y, x - 1, notwalls, content);//LEFT
}

//// check after floodfill ////
bool	is_valid_after_floodfill(t_check *content)
{
	int	y;
	int	x;

	y = -1;
	while (content->dfs_map[++y])
	{
		x = -1;
		while (content->dfs_map[y][++x])
		{
			if (content->dfs_map[y][x] == 'P' || content->dfs_map[y][x] == 'C' || content->dfs_map[y][x] == 'E')
				return (TRUE);//'P', 'C', or 'E' found
		}
	}
	return (FALSE);// NONE of 'P', 'C', or 'E' found
}
