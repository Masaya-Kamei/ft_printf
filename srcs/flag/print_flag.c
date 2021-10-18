/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:31:00 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 14:14:29 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nbr_symbol(t_nbr_symbol symbol)
{
	int		put_len;

	if (symbol == MINUS)
		put_len = write(STDOUT_FILENO, "-", 1);
	else if (symbol == HEX)
		put_len = write(STDOUT_FILENO, "0x", 2);
	else
		put_len = 0;
	return (put_len);
}

static int	print_width(t_flag flag, int len, t_nbr_symbol symbol, char c)
{
	int		put_len;

	if (len < flag.precision && is_nbr_format(flag.type))
		len = flag.precision;
	len += get_symbol_len(symbol);
	if (len < flag.width)
		put_len = putchar_for_size(c, flag.width - len);
	else
		put_len = 0;
	return (put_len);
}

int	print_prefix_width_with_symbol(t_flag flag, int len, t_nbr_symbol symbol)
{
	int		put_len;

	if (flag.minus == 0)
	{
		if (flag.zero
			&& (flag.precision == PRECISION_OFF || is_chars_format(flag.type)))
		{
			put_len = print_nbr_symbol(symbol);
			put_len += print_width(flag, len, symbol, '0');
		}
		else
		{
			put_len = print_width(flag, len, symbol, ' ');
			put_len += print_nbr_symbol(symbol);
		}
	}
	else
		put_len = print_nbr_symbol(symbol);
	return (put_len);
}

int	print_suffix_width(t_flag flag, int len, t_nbr_symbol symbol)
{
	int		put_len;

	if (flag.minus == 1)
		put_len = print_width(flag, len, symbol, ' ');
	else
		put_len = 0;
	return (put_len);
}

int	print_precision(t_flag flag, int len)
{
	int		put_len;

	if (len < flag.precision)
		put_len = putchar_for_size('0', flag.precision - len);
	else
		put_len = 0;
	return (put_len);
}
