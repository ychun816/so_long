/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:28:39 by yilin             #+#    #+#             */
/*   Updated: 2024/08/28 18:57:04 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*collect cake*/
void	track_collect_cakes(t_mlx *data, int y, int x)
{
	if (data->map[(data->p_y) + y][(data->p_x) + x] == 'C')
	{
		data->left_cakes--;
		ft_printf("CAKE COLLECTED 🍰 %d CAKES LEFT!\n", data->left_cakes);
	}
}
