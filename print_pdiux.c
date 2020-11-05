/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pdiux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:20:28 by mkamei            #+#    #+#             */
/*   Updated: 2020/11/05 19:02:26 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digit_base(long n, int base_num)
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

static int	putnbr_base(long n, int base_num, int alpha_size)
{
	char		c;
	static int	len;

	if (n >= base_num)
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

static int	putnbr_with_precision(long n, int n_len, int prefix_len, t_flags flags)
{
	int len;

	len = 0;
	if (flags.type == 'p')
		len += write(1, "0x", 2);
	else if (n < 0)
		len += write(1, "-", 1);
	if (flags.zero == 1 && flags.minus == 0 && n_len + prefix_len < flags.width &&
			(flags.precision == PRECISION_OFF || flags.precision == PRECISION_MINUS))
		len += putchar_num('0', flags.width - n_len - prefix_len);
	else if (n_len < flags.precision)
		len += putchar_num('0', flags.precision - n_len);
	if (n == 0 && flags.precision == 0)
		return (len);
	if (flags.type == 'd' || flags.type == 'i' || flags.type == 'u')
		len += putnbr_base(ABS(n), 10, 0);
	else if (flags.type == 'p' || flags.type == 'x')
		len += putnbr_base(n, 16, ALPHA_SIZE_SMALL);
	else if (flags.type == 'X')
		len += putnbr_base(n, 16, ALPHA_SIZE_LARGE);
	return (len);
}

static int	putnbr_with_flags(long n, int n_len, int prefix_len, t_flags flags)
{
	int len;

	len = 0;
	if (flags.minus == 0)
	{
		if (n_len < flags.precision && flags.precision < flags.width)
			len += putchar_num(' ', flags.width - flags.precision - prefix_len);
		else if (n_len >= flags.precision && n_len + prefix_len < flags.width)
		{
			if (flags.zero == 0 || (flags.precision != PRECISION_OFF && flags.precision != PRECISION_MINUS))
				len += putchar_num(' ', flags.width - n_len - prefix_len);
		}
	}
	len += putnbr_with_precision(n, n_len, prefix_len, flags);
	if (flags.minus == 1)
	{
		if (n_len < flags.precision && flags.precision < flags.width)
			len += putchar_num(' ', flags.width - flags.precision - prefix_len);
		else if (n_len >= flags.precision && n_len + prefix_len < flags.width)
			len += putchar_num(' ', flags.width - n_len - prefix_len);
	}
	return (len);
}

int			print_pdiux(va_list ap, t_flags flags)
{
	long	n;
	int		n_len;
	int		prefix_len;

	if (flags.type == 'p')
		n = (long)va_arg(ap, void *);
	else if (flags.type == 'd' || flags.type == 'i')
		n = va_arg(ap, int);
	else
		n = va_arg(ap, unsigned int);
	if (flags.type == 'p')
		prefix_len = 2;
	else
		prefix_len = (n < 0) ? 1 : 0;
	if (n == 0 && flags.precision == 0)
		n_len = 0;
	else if (flags.type == 'd' || flags.type == 'i' || flags.type == 'u')
		n_len = count_digit_base(ABS(n), 10);
	else
		n_len = count_digit_base(n, 16);
	// if (flags.precision == PRECISION_MINUS)
	// 	flags.precision = n_len;
	return (putnbr_with_flags(n, n_len, prefix_len, flags));
}
