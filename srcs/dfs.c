/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:08:01 by yilin             #+#    #+#             */
/*   Updated: 2024/08/23 15:43:04 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //ft_dfs
 * Performs a depth-first search on a 2d map, starting from a 
 * given position (y, x).
 * The search is limited to positions specified in 'notwalls''s characters.
 * Visited positions are filled with '~'.
 * 
 * @param map The map to perform the depth-first search on.
 * @param y The starting row index.
 * @param x The star
 * @param notwalls A string containing characters that are considered valid positions to visit.
 * 
 * (1) Get the length of the first row to determine the number of columns
 * (2) Get the number of rows in the map
 * (3) Check if: (1) the current position out of bounds
 *               (2) the current character is not in the allowed characters
 *               (3)the current position is already visited (marked as '~')
 * (4) Mark the current position as visited by setting it to '~'
 * (5) If meet a cake(C) => decrement the collectible counter
 * (6) Recursively explore all four possible directions: up, down, right, left
 * 
 * @note Only a valid starting position will fill the paths.
 */
void	ft_dfs(char **map, int y, int x, char *notwalls, t_check *content)
{
	int	rowlen;
	int	n_rows;

	rowlen = ft_strlen(*map);
	n_rows = ft_arraylen((const char **)map);
	if (y < 0 || y >= n_rows || x < 0 || x >= rowlen
        || !ft_strchr(notwalls, map[y][x]) || map[y][x] == '~')
        return ;
	map[y][x] = '~';	
    if (map[y][x] == 'C')
		content->count_cakes--;
	ft_dfs(map, y - 1, x, notwalls, content);
	ft_dfs(map, y + 1, x, notwalls, content);
	ft_dfs(map, y, x + 1, notwalls, content);
	ft_dfs(map, y, x - 1, notwalls, content);
}

// //// check after floodfill ////
// bool	is_valid_after_dfs(t_check *content)
// {
// 	int	y;
// 	int	x;
// a
// 	y = -1;
// 	while (content->dfs_map[++y])
// 	{
// 		x = -1;
// 		while (content->dfs_map[y][++x])
// 		{
// 			if (content->dfs_map[y][x] == 'P' || content->dfs_map[y][x] == 'C' || content->dfs_map[y][x] == 'E')
// 				return (TRUE);//'P', 'C', or 'E' found
// 		}
// 	}
// 	return (FALSE);// NONE of 'P', 'C', or 'E' found
// }
