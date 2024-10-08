/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:08:01 by yilin             #+#    #+#             */
/*   Updated: 2024/08/29 16:37:23 by yilin            ###   ########.fr       */
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
 * @param notwalls string containing characters considered valid elements
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

int check_e = 0;
void	ft_dfs(char **map, t_dfs pos, char *notwalls, t_check *content)
{
	int	rowlen;
	int	n_rows;

	rowlen = ft_strlen(*map);
	n_rows = ft_arraylen((const char **)map);
	if (map[pos.y][pos.x] == 'E')
		check_e = 1;
	if (pos.y < 0 || pos.y >= n_rows || pos.x < 0 || pos.x >= rowlen
		|| map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == '~' ||  map[pos.y][pos.x] == 'E')
		return ;
	if (map[pos.y][pos.x] != 'P')
		map[pos.y][pos.x] = '~';
	ft_dfs(map, (t_dfs){pos.y - 1, pos.x}, notwalls, content);
	ft_dfs(map, (t_dfs){pos.y + 1, pos.x}, notwalls, content);
	ft_dfs(map, (t_dfs){pos.y, pos.x + 1}, notwalls, content);
	ft_dfs(map, (t_dfs){pos.y, pos.x - 1}, notwalls, content);
}

/*check after dfs*/
bool	is_valid_after_dfs(t_check *content)
{
	int	y;
	int	x;

	y = -1;
	while (content->dfs_map[++y])
	{
		x = -1;
		while (content->dfs_map[y][++x])
		{
			if (content->dfs_map[y][x] == 'C')
				return (FALSE);
			if (content->count_exit != 1 || check_e != 1)
				return (FALSE);
		}
	}
	return (TRUE);
}
