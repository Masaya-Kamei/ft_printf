/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:51:28 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 20:00:20 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf_develop.h"

static int	print_nbr(const t_flag flag
	, const unsigned long n, const int base, const t_nbr_symbol symbol)
{
	const int	n_len = count_ulong_digit_in_base(flag, n, base);
	int			put_len;

	put_len = 0;
	put_len += print_prefix_width_with_symbol(flag, n_len, symbol);
	put_len += print_precision(flag, n_len);
	put_len += print_ulong_in_base(flag, n, base);
	put_len += print_suffix_width(flag, n_len, symbol);
	return (put_len);
}

int	print_int(const t_flag flag, va_list ap)
{
	long			n;
	const int		base = 10;
	t_nbr_symbol	symbol;

	n = (long)va_arg(ap, int);
	if (n < 0)
	{
		n *= -1;
		symbol = MINUS;
	}
	else
		symbol = NO_SYMBOL;
	return (print_nbr(flag, n, base, symbol));
}

int	print_uint(const t_flag flag, va_list ap)
{
	const unsigned int	n = va_arg(ap, unsigned int);
	const int			base = 10;
	const t_nbr_symbol	symbol = NO_SYMBOL;

	return (print_nbr(flag, n, base, symbol));
}

int	print_hex(const t_flag flag, va_list ap)
{
	const unsigned int	n = va_arg(ap, unsigned int);
	const int			base = 16;
	const t_nbr_symbol	symbol = NO_SYMBOL;

	return (print_nbr(flag, n, base, symbol));
}

int	print_pointer(const t_flag flag, va_list ap)
{
	const unsigned long	n = (unsigned long)va_arg(ap, void *);
	const int			base = 16;
	const t_nbr_symbol	symbol = HEX;

	return (print_nbr(flag, n, base, symbol));
}
