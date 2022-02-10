/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 12:27:44 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/19 13:00:37 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdio.h>

// Conversions	:c s p d i u x X %
// Flags 		:0 * width precision

int main(void)
{
	char	c = 'c';
	printf("\n[char]\n");
	printf("ret    :%d\n", printf("{%c} ", c));
	printf("ft_ret :%d\n", ft_printf("{%c} ", c));

	char	*s = "aaa";
	printf("\n[string]\n");
	printf("ret    :%d\n", printf("{%s} ", s));
	printf("ft_ret :%d\n", ft_printf("{%s} ", s));

	char	*p = "aaa";
	printf("\n[pointer]\n");
	printf("ret    :%d\n", printf("{%-018.15p} ", p));
	printf("ft_ret :%d\n", ft_printf("{%-018.15p} ", p));


	int		d = 2147483647;
	printf("\n[int]\n");
	printf("ret    :%d\n", printf("{%015.12d} ", d));
	printf("ft_ret :%d\n", ft_printf("{%015.12d} ", d));
	printf("ret    :%d\n", printf("{%0*.*d} ", 4, -4, d));
	printf("ft_ret :%d\n", ft_printf("{%0*.*d} ", 4, -4, d));

	unsigned int	u = 4147483648;
	printf("\n[unsigned int]\n");
	printf("ret    :%d\n", printf("{%15.12u} ", u));
	printf("ft_ret :%d\n", ft_printf("{%15.12u} ", u));

	int 	x = 0x32;
	printf("\n[hex]\n");
	printf("ret    :%d\n", printf("{%-8.5x} ", x));
	printf("ft_ret :%d\n", ft_printf("{%-8.5x} ", x));

	return (0);
}
