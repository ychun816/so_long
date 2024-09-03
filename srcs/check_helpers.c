/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:11:29 by yilin             #+#    #+#             */
/*   Updated: 2024/08/28 19:04:16 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	loop_n_check_elements(char **map, t_check *content)
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
			if (map[y][x] != '1' \
				&& map[y][x] != '0' && map[y][x] != 'P'
				&& map[y][x] != 'E' && map[y][x] != 'C' && map[y][x] != '\n')
				return (FALSE);
		}
	}
	return (TRUE);
}

/** //is line valid
 * @brief Check if a specific line in the map is properly structured,
 * (1) If the first character of the line is not '1' (a wall)=> return false
 * (2) If(wall) -> Loop through the line and check for wall validity
 * 	  => If a "non-wall character" is found in a wall line => return false
 * 	  => If the end of the line is reached => return true (valid wall line)
 * (3) else (not wall) -> Loop through the line
 * - If find '1' && it's not followed by a '\n' OR end-of-line 
 * 	=> skip to the next character.
 * - If 'C' OR an invalid 'E' is found => invlaid
 * @return false if the line is invalid
 */

bool	is_line_wall(char **line, int y)
{
	int	x;

	x = 0;
	if (line[y][x] != '1')
		return (FALSE);
	return (TRUE);
}

bool	is_line_valid(char **line, int y, int wall)
{
	int	x;

	x = 0;
	is_line_wall(line, y);
	while (line[y][++x] && wall)
	{
		if (line[y][x] != '1')
			return (FALSE);
		if (line[y][x + 1] == '\n' || line[y][x + 1] == '\0')
			return (TRUE);
	}
	while (line[y][++x] && !wall)
	{
		if (line[y][x] == '1' && line[y][x + 1] != '\n')
			x++;
		if (line[y][x] == '1' && line[y][x + 1] == '\n')
			return (TRUE);
		if (line[y][x] == 'C' \
			|| ((line[y][x] == 'E' && line[y][x + 1] != '~')
			&& (line[y][x] == 'E' && line[y][x - 1] != '~')
			&& (line[y][x] == 'E' && line[y - 1][x] != '~')
			&& (line[y][x] == 'E' && line[y + 1][x] != '~')))
			return (FALSE);
	}
	return (FALSE);
}
