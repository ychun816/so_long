/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:22 by yilin             #+#    #+#             */
/*   Updated: 2024/08/19 20:01:15 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "setting.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>

// # include "../mlx_linux/mlx_int.h"
// # include <X11/X.h>
# include "../mlx_linux/mlx.h"
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

/* BOOLEAN
typedef enum e_error
{
	TRUE = 1,	
	FALSE = 0,
}	t_error;
*/

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

/* a byte = 8 bits.*/
typedef unsigned char	t_byte;

/*structure for img*/
typedef struct	s_img
{
	void	*ptr;
	char	*pixel_ptr;
	int	bpp;//Bits per pixel
	int	endian;//端序Endianness of the image data "大端和小端（Big endian and Little endian）"
	int	pline_len;//Length of a line of pixels in bytes, used for alignment optimization.
}	t_img;

/*structure for mlx commands*/
typedef struct s_mlx
{
	void	*mlx_ptr;//Connection pointer (e.g., to a graphics library like MiniLibX)
	void	*window;
	t_img	img[SPRITES_NB];//Array of images
	char	**map;//2D array => the game map.
	int	width;
	int	height;
	int	p_x;
	int	p_y;
	int	p_dir;//player's direction
	int	left_collectable;//Number of coins left to collect
	int	moves;
}	t_mlx;

/*structure for check*/
typedef struct s_check
{
	int	player_count;//Number of player start positions
	int	exit_count;//Number of exits
	int	count_collectable;//Number of collectibles
	char	**dfs_map;//2D array used for depth-first search, possibly for pathfinding or validation.
} t_check;

// /*structure for player*/
// typedef struct	s_player
// {
// 	int	x;
// 	int	y;
// 	int	step_count;
// }	t_player;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*SO LONG MAIN*/
int		handle_keyboard(int keyboard, t_mlx *data);
void	handle_player_pos(t_mlx *data, int pos);
void	update_pos_map(t_mlx *data, int y, int x);
char	**read_n_set_map(int fd);

/*ERROR CHECKERS*/
bool	is_pos_blocked(t_mlx *data);
bool	is_map_valid(char **map, char *file_name, t_mlx *data);
bool	is_map_rectangle(char **map);
bool	is_elements_valid(char **map, t_check *content);
bool	is_path_valid(char **map, t_check *content);
bool	is_line_valid(char **line, int y, int wall);

/*EXIT PROGRAM =>QUIT GAME*/
int	exit_program(t_mlx	*data);

/*DISPLAY*/
int	display_window(t_mlx *data, char *filename, int width, int height);
int	load_imgs(t_mlx *data);
void	display_map(t_mlx *data);
void	move_player(t_mlx *data);
void	run_player_animation(t_mlx *data, int *x, int *y, int i);

/*CLEANUP*/
void	free_strs(char **strs, int heap);
int	free_all(int mode, ...);

/*HELPER FUNC*/
int	ft_strslen(const char **array);
long	get_xy(char** map, char element);
int	print_img(t_mlx	*data, void *img_ptr, int x, int y);
char **ft_strsdup(char **array);
void	ft_dfs(char **map, int y, int x, char *notwalls);
char	**ft_strsjoin(char const **strs, char *last_str, int free_strs, int free_str);

#endif
