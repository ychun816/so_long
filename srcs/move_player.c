/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:28:39 by yilin             #+#    #+#             */
/*   Updated: 2024/08/28 18:58:19 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //HANDLE KEYBOARD//
 * @brief process player input -> triggers actions to move player/quit game
 * 
 * @param x extracts x-coordinate frm lower 16 bits of 64-bit value
 * x-coordinate & upper 48 bits are irrelevant for x-coordinate extraction, 
 * the mask 0x0000FFFF effectively zero-out all but the lower 16 bits,
 * giving just the x-coordinate.
 * 
 * @param y extracts the y-coordinate from the upper 32 bits of 64-bit value.
 * moves the upper 32 bits into the lower 32-bit position 
 * => extract the y-coordinate if it stored in upper 32 bits of 64-bit value.
 * @return Function returns 0, as required by mlx_hook
 * @note mlx_hook() => set up event handling for a window in the MiniLibX lib
 */
int	handle_keypress(int keyboard, t_mlx *data)
{
	data->p_y = get_xy(data->map, 'P') >> 32;
	data->p_x = get_xy(data->map, 'P') & 0x0000FFFF;
	if (keyboard == XK_Escape)
		exit_program(data);
	else if (keyboard == XK_w || keyboard == XK_Up)
		check_n_move_player(data, PUP);
	else if (keyboard == XK_d || keyboard == XK_Right)
		check_n_move_player(data, PRIGHT);
	else if (keyboard == XK_s || keyboard == XK_Down)
		check_n_move_player(data, PDOWN);
	else if (keyboard == XK_a || keyboard == XK_Left)
		check_n_move_player(data, PLEFT);
	return (SUCCESS);
}

/** //CHECK N MOVE PLAYER//
 * @brief 
 * move player on game map based frm handle_keypress()
 * If the movement blocked => updates player's position accordingly.
 */
void	check_n_move_player(t_mlx *data, int pos)
{
	data->p_dir = pos;
	if (data->p_dir == PUP && !is_pos_blocked(data))
		update_map(data, -1, 0);
	else if (data->p_dir == PDOWN && !is_pos_blocked(data))
		update_map(data, 1, 0);
	else if (data->p_dir == PRIGHT && !is_pos_blocked(data))
		update_map(data, 0, 1);
	else if (data->p_dir == PLEFT && !is_pos_blocked(data))
		update_map(data, 0, -1);
	move_n_track_player(data);
}

/** //UPDATEMAP//
 * @brief 
 * updates map after the player moves(show player's new position)
 * handles events: 
 * collecting cakes / open exit / check win conditions
 * @param x coordinates: extracts x coordinate (column) 
 * exit & 0xFFFFFFFF -> mask out upper 32 bits 
 * => leaving only the lower 32 bits.
 * @param y coordinates: extracts the y coordinate (row) of exit 
 * exit >> 32 -> shift bits of exit 32 positions to the right
 * 
 * @note print img 
 * x : Calculate x-coordinate in pixels[BLOCK to PIXEL coordinates]
 * y : Calculate y-coordinate in pixels [BLOCK to PIXEL coordinates]
 * => extract lower 32 bits of 'exit'(x-coordinate in map) *BPS(block pixel size)
 * 
 * @note (1) Update player's new position / (2)Clear player's previous position
 * @note If dont clear old pos
 * => both the new and old positions marked as the player’s position! WRONG!
 */
void	update_map(t_mlx *data, int y, int x)
{
	long	exit;

	track_collect_cakes(data, y, x);
	exit = get_xy(data->map, 'E');
	if (data->left_cakes == 0)
	{
		data->map[exit >> 32][exit & 0xFFFFFFFF] = 'E';
		print_img(data, data->img[EXIT2].ptr, \
			(exit & 0xFFFFFFFF) * BPS, (exit >> 32) * BPS);
		mlx_do_sync(data->mlx_ptr);
	}
	if (data->left_cakes == 0 \
		&& data->map[(data->p_y) + y][(data->p_x) + x] == 'E')
	{
		ft_printf("🎖️ YOU WON!!🎖️ In %d moves!\n", data->moves);
		exit_program(data);
	}
	data->map[(data->p_y) + y][(data->p_x) + x] = 'P';
	data->map[data->p_y][data->p_x] = '0';
	print_img(data, data->img[FLOOR].ptr, \
		data->p_x * BPS, data->p_y * BPS);
}

/** // MOVE N DISPLAY PLAYER //
 * @brief
 * - Handles the animation of the player character as it moves, 
 * - updating the display and keeping track of the number of moves.
 * (1) Calculate the player's initial position on the screen
 * (2) Display the player's current image at initial position
 * (3) Synchronize the graphical display
 * (4) Check if the player is blocked from moving => return
 * (5) animate player()
 * (6) Increment and print the move count
 * (7) Disiplay the player's current image at the new positon
 * (8) Synchronize the graphical display again 
 * => guarantees that the animation appears smoothly
*/
void	move_n_track_player(t_mlx *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = data->p_x * BPS;
	y = data->p_y * BPS;
	print_img(data, data->img[data->p_dir].ptr, x, y);
	mlx_do_sync(data->mlx_ptr);
	if (is_pos_blocked(data))
		return ;
	animate_player(data, &x, &y, i);
	ft_printf("moves count: %d\n", ++data->moves);
	print_img(data, data->img[data->p_dir].ptr, x, y);
	mlx_do_sync(data->mlx_ptr);
}

/** // run player animation //
 * @brief
 * - Performs a smooth transition animation
 * - update the player's sprite and position incrementally.
 * - Loop to perform the animation in small steps
 * - PUP / PRIGHT / PDOWN / PLEFT => move player by 2 pixels
 * @note uSleep(milliseconds]): 
 * - create a smooth animation effect
 * - suspend execution for a given number of microseconds 
 * => slow down an animation => creating a delay between each frame.
*/
void	animate_player(t_mlx *data, int *x, int *y, int i)
{
	while (i < BPS / 2)
	{
		if (data->p_dir == PUP)
			*y -= 2;
		else if (data->p_dir == PRIGHT)
			*x += 2;
		else if (data->p_dir == PDOWN)
			*y += 2;
		else if (data->p_dir == PLEFT)
			*x -= 2;
		if (i % 1 == 0)
			print_img(data, data->img[data->p_dir].ptr, *x, *y);
		mlx_do_sync(data->mlx_ptr);
		usleep(12000);
		i++;
	}
}
