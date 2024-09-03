/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:11:51 by yilin             #+#    #+#             */
/*   Updated: 2024/08/28 18:54:41 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //is_gamewindow_oversize//
 * checks:
 * printf("scr_width: %d; scr_height: %d\n", scrn_width, scrn_height);
 * printf("win_width: %d; win_height: %d\n", width, height);
 * 
 */
bool	is_gamewindow_oversize(t_mlx *data, int width, int height)
{	
	int	scrn_width;
	int	scrn_height;

	scrn_width = 0;
	scrn_height = 0;
	mlx_get_screen_size(data->mlx_ptr, &scrn_width, &scrn_height);
	if (width > scrn_width || height > scrn_height)
		return (TRUE);
	return (FALSE);
}

/*Check imgs valid*/
/*STDERR_FILENO = 2*/
void	check_imgs_valid(t_mlx *data)
{
	if (!data->img[WALL].ptr)
		(ft_putstr_fd("Img Error: WALL\n", 2), exit_program(data));
	if (!data->img[FLOOR].ptr)
		(ft_putstr_fd("Img Error: FLOOR\n", 2), exit_program(data));
	if (!data->img[EXIT].ptr)
		(ft_putstr_fd("Img Error: EXIT\n", 2), exit_program(data));
	if (!data->img[EXIT2].ptr)
		(ft_putstr_fd("Img Error: OPEN EXIT\n", 2), exit_program(data));
	if (!data->img[CAKE].ptr)
		(ft_putstr_fd("Img Error: CAKE\n", 2), exit_program(data));
	if (!data->img[PUP].ptr)
		(ft_putstr_fd("Img Error: PUP\n", 2), exit_program(data));
	if (!data->img[PDOWN].ptr)
		(ft_putstr_fd("Img Error: PDOWN\n", 2), exit_program(data));
	if (!data->img[PRIGHT].ptr)
		(ft_putstr_fd("Img Error: PRIGHT\n", 2), exit_program(data));
	if (!data->img[PLEFT].ptr)
		(ft_putstr_fd("Img Error: PLEFT\n", 2), exit_program(data));
}

/** //is pos blocked //
 * Checks if the given position is blocked in the specified direction.
 * @return TRUE(1) if the position is blocked
 * @return FALSE(0) if the position is NOT blocked->passable
 **/
bool	is_pos_blocked(t_mlx *data)
{
	if (data->p_dir == PUP && (data->map[data->p_y - 1][data->p_x] == '1'
		|| (data->map[data->p_y - 1][data->p_x] == 'E' \
		&& data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PRIGHT \
		&& (data->map[data->p_y][data->p_x + 1] == '1'
		|| (data->map[data->p_y][data->p_x + 1] == 'E' \
		&& data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PDOWN && (data->map[data->p_y + 1][data->p_x] == '1'
		|| (data->map[data->p_y + 1][data->p_x] == 'E' \
		&& data->left_cakes != 0)))
		return (TRUE);
	else if (data->p_dir == PLEFT && (data->map[data->p_y][data->p_x - 1] == '1'
		|| (data->map[data->p_y][data->p_x - 1] == 'E' \
		&& data->left_cakes != 0)))
		return (TRUE);
	return (FALSE);
}
