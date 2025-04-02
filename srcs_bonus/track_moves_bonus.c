/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_moves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:28:39 by yilin             #+#    #+#             */
/*   Updated: 2024/09/03 17:55:32 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*check meet villain*/
void	check_meet_villain(t_mlx *data, int y, int x)
{
	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'V')
	{
		ft_printf("💀💀 AHHH U DEAD!!💀💀\n");
		exit_program(data);
	}
}

/*collect cake*/
void	track_collect_cakes(t_mlx *data, int y, int x)
{
	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'C')
	{
		data->left_cakes--;
		ft_printf("CAKE COLLECTED 🍰 %d CAKES LEFT!\n", data->left_cakes);
	}
}
