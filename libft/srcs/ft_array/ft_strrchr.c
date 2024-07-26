/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:59:21 by yilin             #+#    #+#             */
/*   Updated: 2024/05/25 17:47:51 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if (c == 0)
		return ((char *)str + i);
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// int	main()
// {
// 	char *str = "helloyooya!";
// 	char	*result;

// 	result = ft_strrchr(str, 'y');
// 	printf("%s\n", result);
// }

// int main()
// {
// 		char s[] = "tripouille";
// 		char c = 't';
// 		c += 265;
// 		char *test = ft_strrchr(s , 'y');
// 		printf("%c\n", c);
// 		printf("%s\n", ft_strrchr(s , 'y'));		
// }