/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:26:48 by yilin             #+#    #+#             */
/*   Updated: 2024/08/11 20:54:18 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//// free strs //// 
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

//// ft_free ////
/**
 * @brief Frees various types of pointers based on the specified mode.
 * 
 * prototyped return "int" instead of "void" -> communicate status
 * 
 * This function handles freeing different types of pointers. It accepts a mode that
 * determines the type of pointer and frees it accordingly. The function continues
 * to free pointers until a NULL pointer is encountered. The possible modes are:
 * 
 * - Mode 1: Free a single pointer (void *).
 * - Mode 2: Free a 2D array of strings (char **), using the free_strs function.
 * - Mode 3: Free a linked list (t_list **), using the ft_lstclear function.
 * 
 * @param mode An integer specifying the type of pointer to free (1, 2, or 3).
 * @param ... A variable number of arguments representing the pointers to be freed.
 *            The argument list must end with a NULL pointer.
 * @return 1 on success. The return value is not used in this implementation.
 */
int	ft_free(int mode, ...)
{
	va_list	args;
	void	*ptr;

	// Initialize the va_list variable with the last fixed argument (mode)
	va_start(args, mode);
	// Retrieve the first pointer argument from the variadic arguments
	ptr = va_arg(args, void *);
	// loop until meet NULL
	while (ptr)
	{
		// Based on different modes =>perform the matching memory deallocation
		//mode == 1 (single pointer) => Free a single pointer.
		if (mode == 1)
			free(ptr);
		//mode == 2 (2D array) =>
		else if (mode == 2)
			free_strs((char **)ptr, 1);//heap == 1 => free the top-level array, which was allocated separately from the individual strings.
		//mode == 3 (linked list) => free linked list
		else if (mode == 3)
			ft_lstclear((t_list **)ptr, free);
		else
		{
			// If mode is invalid, print an error message
			if (mode < 1 || mode > 3)
			{
				ft_putstr_fd("Error: ft_free: WRONG MODE\n", STDERR_FILENO);
				va_end(args);//cleanup the list
				return (EXIT_FAILURE); //return(EXIT_FAILURE)/return(1) due to error
			}		
		}
		// loop->Get the next pointer to process
		ptr = va_arg(args, void *);
	}
	va_end(args);// Clean up the va_list after processing all arguments
	return (EXIT_SUCCESS);//return(0)-> SUCCESS
}

/*
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	(del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}*/
