/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:09:21 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/17 12:14:29 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_chars_width(t_flag flag, int str_len, bool is_prefix)
{
	int		output_len;

	if (is_prefix && flag.minus)
		return (0);
	else if (!is_prefix && !flag.minus)
		return (0);
	if (flag.width > str_len)
	{
		if (is_prefix && flag.zero)
			output_len = putchar_num('0', flag.width - str_len);
		else
			output_len = putchar_num(' ', flag.width - str_len);
	}
	return (output_len);
}

int	print_char(const t_flag flag, va_list ap, bool is_percent)
{
	char	c;
	int		output_len;

	if (is_percent)
		c = '%';
	else
		c = va_arg(ap, int);
	output_len = 0;
	output_len += print_chars_width(flag, 1, 1);
	output_len += write(1, &c, 1);
	output_len += print_chars_width(flag, 1, 0);
	return (output_len);
}

int	print_str(const t_flag flag, va_list ap)
{
	char	*str;
	int		str_len;
	int		output_len;

	str = va_arg(ap, char *);
	if (str == NULL)
		str_len = 6;
	else
		str_len = ft_strlen(str);
	if (flag.precision != PRECISION_OFF && str_len > flag.precision)
		str_len = flag.precision;
	output_len = 0;
	output_len += print_chars_prefix(flag, str_len, 1);
	if (str == NULL)
		output_len += write(1, "(null)", str_len);
	else
		output_len += write(1, str, str_len);
	output_len += print_chars_suffix(flag, str_len, 0);
	return (output_len);
}
