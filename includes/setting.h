/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:00:05 by yilin             #+#    #+#             */
/*   Updated: 2024/08/23 15:36:01 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

/* ************************************************************************** */
/*                          DEFAULT BG COLOR                                  */
/* ************************************************************************** */

# define DEFAULT_COLOR 0xf1efdf SPRITES_NB

/* ************************************************************************** */
/*                          SPRITE/PLAYER SETTING                             */
/* ************************************************************************** */

// Bytes Per Sprite: size of each sprite data in bytes.
# define BPS 32

// Total number of different sprites (updated for your new set of sprites)
# define SPRITES_NB 9

// Sprite type definitions with unique identifiers
# define WALL 0 // Identifier for wall sprite
# define FLOOR 1
# define EXIT 2
# define EXIT2 3
# define CAKE 4
# define PUP 5
# define PDOWN 6
# define PRIGHT 7
# define PLEFT 8

/*REF
# define SPRITES_NB 17

# define WALL 0
# define FLOOR 1
# define EXIT1 2
# define EXIT2 3
# define COIN 4

// player facing down
# define PDOWN 5
# define PDOWN1 6
# define PDOWN2 7

// player facing right
# define PRIGHT 8
# define PRIGHT1 9
# define PRIGHT2 10

// player facing up
# define PUP 11
# define PUP1 12
# define PUP2 13

// player facing left
# define PLEFT 14
# define PLEFT1 15
# define PLEFT2 16
*/

/* ************************************************************************** */
/*                                     PATHS                                  */
/* ************************************************************************** */
//example
# define WALL_PATH "sprites/wall.xpm"
# define FLOOR_PATH "sprites/floor.xpm"
# define EXIT_PATH "sprites/exit.xpm"
# define EXIT2_PATH "sprites/exit2.xpm"
# define CAKE_PATH "sprites/collectable.xpm"
# define PUP_PATH "sprites/pup.xpm" 
# define PDOWN_PATH "sprites/pdown.xpm"
# define PRIGHT_PATH "sprites/pright.xpm" 
# define PLEFT_PATH "sprites/pleft.xpm" 

/* ************************************************************************** */
/*                              ERROR MESSAGE                                 */
/* ************************************************************************** */

#endif