/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pdiux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:20:28 by mkamei            #+#    #+#             */
/*   Updated: 2020/11/06 12:17:08 by mkamei           ###   ########.fr       */
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

static int	putspace_only_width(int n_len, int prefix_len, t_flags flags)
{
	int len;
	int nbr_with_precision_len;

	len = 0;
	if (n_len < flags.precision)
		nbr_with_precision_len = flags.precision + prefix_len;
	else
	{
		if (flags.minus == 0 && flags.zero == 1
								&& flags.precision == PRECISION_OFF)
			nbr_with_precision_len = PUT_ZERO_SO_SKIP;
		else
			nbr_with_precision_len = n_len + prefix_len;
	}
	if (nbr_with_precision_len < flags.width &&
							nbr_with_precision_len != PUT_ZERO_SO_SKIP)
		len += putchar_num(' ', flags.width - nbr_with_precision_len);
	return (len);
}

static int	putnbr_with_flags(unsigned long n, int n_len,
											int prefix_len, t_flags flags)
{
	int len;

	len = 0;
	if (flags.minus == 0)
		len += putspace_only_width(n_len, prefix_len, flags);
	if (prefix_len == 2)
		len += write(1, "0x", 2);
	else if (prefix_len == 1)
		len += write(1, "-", 1);
	if (flags.zero == 1 && flags.minus == 0 && flags.precision == PRECISION_OFF
										&& n_len + prefix_len < flags.width)
		len += putchar_num('0', flags.width - n_len - prefix_len);
	else if (n_len < flags.precision)
		len += putchar_num('0', flags.precision - n_len);
	if (n == 0 && flags.precision == 0)
		;
	else if (flags.type == 'd' || flags.type == 'i' || flags.type == 'u')
		len += putnbr_base(n, 10, 0);
	else if (flags.type == 'p' || flags.type == 'x')
		len += putnbr_base(n, 16, ALPHA_SIZE_SMALL);
	else if (flags.type == 'X')
		len += putnbr_base(n, 16, ALPHA_SIZE_LARGE);
	if (flags.minus == 1)
		len += putspace_only_width(n_len, prefix_len, flags);
	return (len);
}

int			print_pdiux(va_list ap, t_flags flags)
{
	unsigned long	n;
	long			l;
	int				n_len;
	int				prefix_len;

	if (flags.type == 'p')
		n = (unsigned long)va_arg(ap, void *);
	else if (flags.type == 'd' || flags.type == 'i')
	{
		l = va_arg(ap, int);
		n = (l < 0) ? -l : l;
	}
	else
		n = va_arg(ap, unsigned int);
	if (flags.type == 'd' || flags.type == 'i')
		prefix_len = (l < 0) ? 1 : 0;
	else
		prefix_len = (flags.type == 'p') ? 2 : 0;
	if (n == 0 && flags.precision == 0)
		n_len = 0;
	else if (flags.type == 'd' || flags.type == 'i' || flags.type == 'u')
		n_len = count_digit_base(n, 10);
	else
		n_len = count_digit_base(n, 16);
	return (putnbr_with_flags(n, n_len, prefix_len, flags));
}
