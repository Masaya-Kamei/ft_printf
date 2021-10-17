/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:54:29 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/16 18:25:06 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(const t_flag flag, va_list ap)
{
	int		output_len;

	if (flag.type == 'c' || flag.type == '%')
		output_len = print_char(flag, ap, flag.type == '%');
	else if (flag.type == 's')
		output_len = print_str(flag, ap);
	else if (flag.type == 'p')
		output_len = print_pointer(flag, ap);
	else if (flag.type == 'd' || flag.type == 'i')
		output_len = print_int(flag, ap);
	else if (flag.type == 'u')
		output_len = print_unsigned_int(flag, ap);
	else if (flag.type == 'x' || flag.type == 'X')
		output_len = print_hex(flag, ap, flag.type == 'X');
	else
		output_len = 0;
	return (output_len);
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	t_flag		flag;
	int			i;
	int			output_len;

	va_start(ap, s);
	i = 0;
	output_len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			i += read_minus_and_zero(&s[i], &flag);
			i += read_width(&s[i], &flag, ap);
			i += read_precision(&s[i], &flag, ap);
			i += read_type(&s[i], &flag);
			output_len += print_format(flag, ap);
		}
		else
			output_len += write(1, &s[i++], 1);
	}
	va_end(ap);
	return (output_len);
}
