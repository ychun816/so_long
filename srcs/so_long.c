/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:21:31 by yilin             #+#    #+#             */
/*   Updated: 2024/07/27 20:45:12 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(void)
{
    void *mlx;
 
    mlx = mlx_init();
    if (!mlx)
    {
    // Handle the error.
        return (1);
    }
    // Do some cool graphical stuff here…
    // Clean up before exiting. The Display struct and the xvar struct
    mlx_destroy_display(mlx);
    free(mlx);
    return (0);
}