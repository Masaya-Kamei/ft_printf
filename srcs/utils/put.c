/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:51:56 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/16 17:56:28 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_for_size(const char c, const int size)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}
