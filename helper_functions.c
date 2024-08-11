/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:28:32 by yilin             #+#    #+#             */
/*   Updated: 2024/08/11 21:07:08 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


//// ft_arraylen ////
int	ft_arraylen(const char **array) TODO:
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i); 	
}

/// get_xy ////
get_xy(char** map, char status)TODO:
{
	
	//status == 'E' =>
	
}


/// print_img ////
print_img(data, data->img[EXIT1].ptr , (exit & 0xFFFFFFFF)* BPS, (exit >> 32) * BPS)