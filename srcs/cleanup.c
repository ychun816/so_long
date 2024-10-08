/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:26:48 by yilin             #+#    #+#             */
/*   Updated: 2024/08/27 19:26:47 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/** //free strs*/
void	free_strs(char **strs, int heap)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	if (heap)
		free(strs);
}

/** free_all
 * @brief 
 * Frees various types of pointers based on the specified mode.
 * - Mode 1: Free a single pointer (void *) => free()
 * - Mode 2: Free a 2D array of strings (char **) =>free_strs()
 * - Mode 3: Free a linked list (t_list **) => ft_lstclear()
 * 
 * @param mode integer specifying ptr type to free (1, 2, or 3).
 * @param ... A variable number of arguments-> the pointers to be freed.
 * @note The argument list must end with a NULL pointer.
 * Initialize the va_list variable with the last fixed argument (mode)
 * Retrieve the first pointer argument from the variadic arguments
 * Loop until meet NULL -> while (ptr)
 *  => Based on different modes =>perform the matching memory deallocation
 *  => If mode is invalid, print an error message
 * @return 1 on success.
 */
int	free_all(int mode, ...)
{
	va_list	args;
	void	*ptr;

	va_start(args, mode);
	ptr = va_arg(args, void *);
	while (ptr)
	{
		if (mode == 1)
			free(ptr);
		else if (mode == 2)
			free_strs((char **)ptr, 1);
		else if (mode == 3)
			ft_lstclear((t_list **)ptr, free);
		else
		{
			if (mode < 1 || mode > 3)
			{
				ft_putstr_fd("Error: ft_free: WRONG MODE\n", STDERR_FILENO);
				va_end(args);
				return (FAILURE);
			}		
		}
		ptr = va_arg(args, void *);
	}
	return (va_end(args), SUCCESS);
}
