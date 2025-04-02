/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/08/29 17:22:48 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //read_n_set_map
 * Declare (result)-> store lines and a string(line) for the current line
 * (1) If the file descriptor (fd) is invalid => NULL
 * (2) Read lines (get next line) -> If reading fails (no content) => NULL
 * (3) Allocate memory for 2 pointers to store:
 *     (a) pointer to one line + (b)pointer to a NULL terminator
 * (4) If memory allocation fails => return NULL
 * (5) Read first line from the file.
 * (6) Indicate the end of the strs. -> result[1] = NULL;
 * (7) Loop until all lines are read from the file 
 *     => Read the next line from the file
 * 	   => Append the line to the result strs using ft_strsjoin 
 * 		  -> free both result and line as needed
 */
char	**read_n_set_map(int fd)
{
	char	**result;
	char	*line;

	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = line;
	result[1] = NULL;
	while (line)
	{
		line = get_next_line(fd);
		result = ft_strsjoin((char const **)result, line, TRUE, TRUE);
		if (*result == NULL)
			break ;
	}
	return (result);
}

/** //MAIN//
 * (1) open the map file
 * (2) declare n initialize the data structure
 * (3) Check if the map valid && if file as arg => exit program if invalid
 * (4) Get map dimensions => measure the map's width and height
 * @note ft_strlen: measure length of a single row (width)
 * @note ft_arraylen: measure the number of rows (height) 
 * 		 => operates on a 2D array => return number of rows(height) in that array.
 * (5) display window() => load_imgs() => display_map()
 * (6) Set key press hook
 * @note mlx_hook(data.window, 2, 1L << 0, handle_keypress, &data):
 *       1L: long int; <<: bitwise op(shift to left)
 * 		 => Specify an "event mask" for a key press event = a key being pressed
 * (7) Set window close hook
 * @note mlx_hook(data.window,17, 1L << 17, exit_program, &data):
 *       Shifts the number 1 left by 17 positions 
 * 		 => Specify an "event mask" for a window close event 
 *       => clicking the close button on the window
 * (8) Start the event loop
 * (9) Exit program
 * @note ft_strlen((const char *)data.map[0]) - 1 => rid of '\n'
 */
int	main(int ac, char **av)
{
	t_mlx	data;
	int		fd;

	fd = open(av[1], O_RDONLY);
	data = (t_mlx){NULL, NULL, {{NULL, NULL, 0, 0, 0}},
		read_n_set_map(fd), 0, 0, 0, 0, 0, 0, 0};
	close(fd);
	if (!is_map_valid(data.map, av[1], &data) || ac <= 1)
		return (exit_program(&data), FAILURE);
	data.width = ft_strlen((const char *)data.map[0]) - 1;
	data.height = ft_arraylen((const char **)data.map);
	display_window(&data, "so_long", data.width, data.height);
	load_imgs(&data);
	init_map(&data);
	mlx_hook(data.window, 2, 1L << 0, handle_keypress, &data);
	mlx_hook(data.window, 17, 1L << 17, exit_program, &data);
	mlx_loop(data.mlx_ptr);
	exit_program(&data);
	return (SUCCESS);
}
