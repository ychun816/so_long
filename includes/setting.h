/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:00:05 by yilin             #+#    #+#             */
/*   Updated: 2024/08/27 19:49:32 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

/* ************************************************************************** */
/*                          DEFAULT BG COLOR                                  */
/* ************************************************************************** */

// # define DEFAULT_COLOR 0xf1efdf

/* ************************************************************************** */
/*                          SPRITE/PLAYER SETTING                             */
/* ************************************************************************** */

// Bytes Per Sprite: size of each sprite data in bytes.
# define BPS 32

// Total number of different sprites (updated for your new set of sprites)
# define SPRITES_NB 10

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
# define VILLAIN 9

/* ************************************************************************** */
/*                                     PATHS                                  */
/* ************************************************************************** */

# define W_P "sprites/wall.xpm"
# define F_P "sprites/floor.xpm"
# define E_P "sprites/exit.xpm"
# define E2_P "sprites/exit2.xpm"
# define C_P "sprites/cake.xpm"
# define PUP_P "sprites/pup.xpm" 
# define PDWN_P "sprites/pdown.xpm"
# define PR_P "sprites/pright.xpm" 
# define PL_P "sprites/pleft.xpm"
# define V_P "sprites/villain.xpm"

/* ************************************************************************** */
/*                              ERROR MESSAGE                                 */
/* ************************************************************************** */

#endif