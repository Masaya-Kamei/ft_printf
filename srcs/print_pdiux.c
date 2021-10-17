/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pdiux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:20:28 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/16 18:25:39 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digit_base(unsigned long n, int base_num)
{
	int		n_len;

	if (n == 0)
		return (1);
	n_len = 0;
	while (n > 0)
	{
		n_len++;
		n = n / base_num;
	}
	return (n_len);
}

static int	putnbr_base(unsigned long n, int base_num, int alpha_size)
{
	char		c;
	static int	len;

	if (n >= (unsigned long)base_num)
		putnbr_base(n / base_num, base_num, alpha_size);
	else
		len = 0;
	if (base_num == 16 && n % base_num >= 10)
	{
		if (alpha_size == ALPHA_SIZE_LARGE)
			c = n % base_num + '0' + 7;
		else
			c = n % base_num + '0' + 39;
	}
	else
		c = n % base_num + '0';
	len += write(1, &c, 1);
	return (len);
}

static int	putspace_only_width(int n_len, int prefix_len, t_flag flag)
{
	int len;
	int nbr_with_precision_len;

	len = 0;
	if (n_len < flag.precision)
		nbr_with_precision_len = flag.precision + prefix_len;
	else
	{
		if (flag.minus == 0 && flag.zero == 1
								&& flag.precision == PRECISION_OFF)
			nbr_with_precision_len = PUT_ZERO_SO_SKIP;
		else
			nbr_with_precision_len = n_len + prefix_len;
	}
	if (nbr_with_precision_len < flag.width &&
							nbr_with_precision_len != PUT_ZERO_SO_SKIP)
		len += putchar_num(' ', flag.width - nbr_with_precision_len);
	return (len);
}

static int	putnbr_with_flags(unsigned long n, int n_len,
											int prefix_len, t_flag flag)
{
	int len;

	len = 0;
	if (flag.minus == 0)
		len += putspace_only_width(n_len, prefix_len, flag);
	if (prefix_len == 2)
		len += write(1, "0x", 2);
	else if (prefix_len == 1)
		len += write(1, "-", 1);
	if (flag.zero == 1 && flag.minus == 0 && flag.precision == PRECISION_OFF
										&& n_len + prefix_len < flag.width)
		len += putchar_num('0', flag.width - n_len - prefix_len);
	else if (n_len < flag.precision)
		len += putchar_num('0', flag.precision - n_len);
	if (n == 0 && flag.precision == 0)
		;
	else if (flag.type == 'd' || flag.type == 'i' || flag.type == 'u')
		len += putnbr_base(n, 10, 0);
	else if (flag.type == 'p' || flag.type == 'x')
		len += putnbr_base(n, 16, ALPHA_SIZE_SMALL);
	else if (flag.type == 'X')
		len += putnbr_base(n, 16, ALPHA_SIZE_LARGE);
	if (flag.minus == 1)
		len += putspace_only_width(n_len, prefix_len, flag);
	return (len);
}

int			print_pdiux(va_list ap, t_flag flag)
{
	unsigned long	n;
	long			l;
	int				n_len;
	int				prefix_len;

	if (flag.type == 'p')
		n = (unsigned long)va_arg(ap, void *);
	else if (flag.type == 'd' || flag.type == 'i')
	{
		l = va_arg(ap, int);
		n = (l < 0) ? -l : l;
	}
	else
		n = va_arg(ap, unsigned int);
	if (flag.type == 'd' || flag.type == 'i')
		prefix_len = (l < 0) ? 1 : 0;
	else
		prefix_len = (flag.type == 'p') ? 2 : 0;
	if (n == 0 && flag.precision == 0)
		n_len = 0;
	else if (flag.type == 'd' || flag.type == 'i' || flag.type == 'u')
		n_len = count_digit_base(n, 10);
	else
		n_len = count_digit_base(n, 16);
	return (putnbr_with_flags(n, n_len, prefix_len, flag));
}
