/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:00:05 by yilin             #+#    #+#             */
/*   Updated: 2024/07/30 17:11:43 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

/* ************************************************************************** */
/*                          DEFAULT BG COLOR                                  */
/* ************************************************************************** */

# define DEFAULT_COLOR 0xf1efdf

/* ************************************************************************** */
/*                          SPRITE/PLAYER SETTING                             */
/* ************************************************************************** */
// Bytes Per Sprite
# define BPS 32

# define SPRITES_NB 17

# define WALL 0
# define FLOOR 1
# define EXIT1 2
# define EXIT2 3
# define COLLECTABLE 4

// player facing down
# define PDOWN 5
# define PDOWN1 6
# define PDOWN2 7

// player facing up
# define PUP 8
# define PUP1 9
# define PUP2 10

// player facing left
# define PLEFT 11
# define PLEFT1 12
# define PLEFT2 13

// player facing right
# define PRIGHT 14
# define PRIGHT1 15
# define PRIGHT2 16

/* ************************************************************************** */
/*                                     PATHS                                  */
/* ************************************************************************** */
//example
# define WALL_P "sprites/wall.xpm"
# define FLOOR_P "sprites/floor.xpm"
# define EXIT1_P "sprites/exit_open.xpm"
# define EXIT2_P "sprites/exit_closed.xpm"

/* ************************************************************************** */
/*                              ERROR MESSAGE                                 */
/* ************************************************************************** */

# define ERR_MALLOC "Error\nMalloc failed\n"



#endif