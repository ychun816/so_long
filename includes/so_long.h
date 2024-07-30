/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:22 by yilin             #+#    #+#             */
/*   Updated: 2024/07/30 17:04:54 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "setting.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

# include "../mlx_linux/mlx_int.h"
# include "../mlx_linux/mlx.h"

# include <unistd.h>
# include <stdio.h>

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>

/* ************************************************************************** */
/*                                STRUCTURE                                   */
/* ************************************************************************** */

/*enum def*/
// if (is_true == FALSE)
// {
// 	return (SUCCESS);
// }
/*
typedef enum e_error
{
	FALSE = 0,
	TRUE = 1,	
}	t_error;
*/

/* a byte = 8 bits.*/
// typedef unsigned char	t_byte;

/*structure for img*/
typedef struct	s_img
{
	void	*ptr;
	char	*pixel_ptr;
	int	bpp;//Bits per pixel
	int	endian;//Endianness of the image data
	int	pline_len;//Length of a line of pixels in bytes, used for alignment optimization.
}	t_img;

/*structure for player*/
typedef struct	s_player
{
	int	x;
	int	y;
	int	step_count;
}	t_player;

/*structure for mlx commands*/
typedef struct s_mlx
{
	void	*mlx_ptr;//Connection pointer (e.g., to a graphics library like MiniLibX)
	void	*window_ptr;
	t_img	img[SPRITES_NB];//Array of images
	char	**map;//2D array => the game map.
	int	width;
	int	height;
	int	collectable_left;//Number of coins left to collect
	int	player_x;
	int	player_y;
	int	player_dir;//player's direction
}	t_mlx;

/*structure for check*/
typedef struct s_check
{
	int	player_count;//Number of player start positions
	int	exit_count;//Number of exits
	int	count_count;//Number of collectibles
	char	**dfsmap;//2D array used for depth-first search, possibly for pathfinding or validation.
};

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*EXIT PROGRAM =>QUIT GAME*/

/*ERROR CHECK*/

/*MAIN*/

/*DISPLAY*/

/*HELPER FUNC*/


#endif
