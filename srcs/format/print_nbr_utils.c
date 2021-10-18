/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 20:57:38 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 12:24:22 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_ulong_digit_in_base(t_flag flag, unsigned long n, int base)
{
	int		n_len;

	if (n == 0)
	{
		if (flag.precision == 0)
			return (0);
		else
			return (1);
	}
	n_len = 0;
	while (n > 0)
	{
		n_len++;
		n = n / base;
	}
	return (n_len);
}

static int	rec_print_ulong_in_base(t_flag flag, unsigned long n, int base)
{
	char	c;
	int		put_len;

	if (n == 0)
		return (0);
	put_len = rec_print_ulong_in_base(flag, n / base, base);
	if (base == 16 && n % base >= 10)
	{
		if (flag.type == 'X')
			c = n % base + '0' + 7;
		else
			c = n % base + '0' + 39;
	}
	else
		c = n % base + '0';
	put_len += write(1, &c, 1);
	return (put_len);
}

int	print_ulong_in_base(t_flag flag, unsigned long n, int base)
{
	int		put_len;

	if (n == 0)
	{
		if (flag.precision == 0)
			put_len = 0;
		else
			put_len = write(1, "0", 1);
	}
	else
		put_len = rec_print_ulong_in_base(flag, n, base);
	return (put_len);
}
