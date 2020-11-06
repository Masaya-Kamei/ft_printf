/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:09:21 by mkamei            #+#    #+#             */
/*   Updated: 2020/11/06 10:34:13 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		putchar_num(char c, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int		print_c(va_list ap, t_flags flags, int percent)
{
	char	c;
	int		len;

	if (percent == PERCENT_ON)
		c = '%';
	else
		c = va_arg(ap, int);
	len = 0;
	if (flags.minus == 0 && flags.width > 1)
	{
		if (flags.zero == 1)
			len += putchar_num('0', flags.width - 1);
		else
			len += putchar_num(' ', flags.width - 1);
	}
	len += write(1, &c, 1);
	if (flags.minus == 1 && flags.width > 1)
		len += putchar_num(' ', flags.width - 1);
	return (len);
}

int		print_s(va_list ap, t_flags flags)
{
	char	*str;
	int		str_len;
	int		len;

	str = va_arg(ap, char *);
	str_len = (str == NULL) ? 6 : ft_strlen(str);
	if (str_len > flags.precision && flags.precision != PRECISION_OFF)
		str_len = flags.precision;
	len = 0;
	if (flags.minus == 0 && flags.width > str_len)
	{
		if (flags.zero == 1)
			len += putchar_num('0', flags.width - str_len);
		else
			len += putchar_num(' ', flags.width - str_len);
	}
	if (str == NULL)
		len += write(1, "(null)", str_len);
	else
		len += write(1, str, str_len);
	if (flags.minus == 1 && flags.width > str_len)
		len += putchar_num(' ', flags.width - str_len);
	return (len);
}
