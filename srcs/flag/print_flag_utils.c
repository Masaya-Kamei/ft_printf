/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 20:57:02 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 14:23:39 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_for_size(const char c, const int size)
{
	int		put_len;

	put_len = 0;
	while (put_len < size)
	{
		write(1, &c, 1);
		put_len++;
	}
	return (put_len);
}

int	get_symbol_len(t_nbr_symbol symbol)
{
	int		symbol_len;

	if (symbol == MINUS)
		symbol_len = 1;
	else if (symbol == HEX)
		symbol_len = 2;
	else
		symbol_len = 0;
	return (symbol_len);
}

bool	is_nbr_format(t_format_type type)
{
	return (type == 'i' || type == 'd' || type == 'x'
		|| type == 'X' || type == 'u' || type == 'p');
}

bool	is_chars_format(t_format_type type)
{
	return (type == 'c' || type == 's' || type == '%');
}
