/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:03:22 by yilin             #+#    #+#             */
/*   Updated: 2024/09/03 17:56:28 by yilin            ###   ########.fr       */
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

# include "../mlx_linux/mlx.h"
// # include "mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>

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
# define FAILURE 1

/* a byte = 8 bits.*/
typedef unsigned char	t_byte;

/*structure for img*/
/*Bits per pixel*/
/*端序Endianness of the image data "大端和小端（Big endian and Little endian）"*/
/*Length of a line of pixels in bytes, used for alignment optimization.*/
typedef struct s_img
{
	void	*ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		pline_len;
}	t_img;

/*structure for mlx commands*/
/*Connection pointer (e.g., to a graphics library like MiniLibX)*/
/*Array of images*/
/*2D array => the game map.*/

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window;
	t_img	img[SPRITES_NB];
	char	**map;
	int		width;
	int		height;
	int		p_x;
	int		p_y;
	int		p_dir;
	int		left_cakes;
	int		moves;
}	t_mlx;

/*structure for check*/
typedef struct s_check
{
	char	**dfs_map;
	int		count_player;
	int		count_exit;
	int		count_cakes;
	int		count_villains;
}	t_check;

/*structure for dfs y/x*/
typedef struct s_dfs
{
	int	y;
	int	x;
}	t_dfs;

/* ************************************************************************** */
/*                                FUNCTIONS                                   */
/* ************************************************************************** */

/*SO LONG MAIN*/
char	**read_n_set_map(int fd);

/*CHECK DISPLAY*/
bool	is_gamewindow_oversize(t_mlx *data, int width, int height);
void	check_imgs_valid(t_mlx *data);
bool	is_pos_blocked(t_mlx *data);

/*DISPLAY*/
int		display_window(t_mlx *data, char *filename, int width, int height);
bool	is_gamewindow_oversize(t_mlx *data, int width, int height);
int		load_imgs(t_mlx *data);
void	init_map(t_mlx *data);

/*CHECK MAP*/
bool	is_map_valid(char **map, char *file_name, t_mlx *data);
bool	is_map_rectangle(char **map);
bool	is_elements_valid(char **map, t_check *content);
bool	is_path_valid(char **map, t_check *ctnt);

/*CHECK HELPERS*/
bool	loop_n_check_elements(char **map, t_check *content);
bool	is_line_wall(char **line, int y);
bool	is_middle_line_valid(char **line, int y, int wall);
bool	is_line_valid(char **line, int y, int wall);

/*dfs*/
void	ft_dfs(char **map, t_dfs pos, char *notwalls, t_check *content);
bool	is_valid_after_dfs(t_check *content);

/*MOVE PLAYER*/
int		handle_keypress(int keyboard, t_mlx *data);
void	check_n_move_player(t_mlx *data, int pos);
void	update_map(t_mlx *data, int y, int x);
void	move_n_track_player(t_mlx *data);
void	animate_player(t_mlx *data, int *x, int *y, int i);

/*TRACK MOVES*/
void	check_meet_villain(t_mlx *data, int y, int x);
void	track_collect_cakes(t_mlx *data, int y, int x);

/*EXIT PROGRAM =>QUIT GAME*/
int		exit_program(t_mlx	*data);

/*CLEANUP*/
void	free_strs(char **strs, int heap);
int		free_all(int mode, ...);

/*HELPER FUNC*/
size_t	ft_arraylen(const char **arrays);
long	get_xy(char **map, char element);
int		print_img(t_mlx	*data, void *img_ptr, int x, int y);
char	**ft_arraydup(char **array);
char	**ft_strsjoin(char const **strs, char *end_s, int ss_fr, int s_fr);
/*void	test_display_map(t_mlx *data);*/
/*void	test_display_dfsmap(char **map);*/

#endif