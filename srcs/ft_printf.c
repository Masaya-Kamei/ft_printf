/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:54:29 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 20:01:39 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf_develop.h"

static int	print_format(const t_flag flag, va_list ap)
{
	int		put_len;

	if (flag.type == 'c' || flag.type == '%')
		put_len = print_char(flag, ap);
	else if (flag.type == 's')
		put_len = print_str(flag, ap);
	else if (flag.type == 'p')
		put_len = print_pointer(flag, ap);
	else if (flag.type == 'd' || flag.type == 'i')
		put_len = print_int(flag, ap);
	else if (flag.type == 'u')
		put_len = print_uint(flag, ap);
	else if (flag.type == 'x' || flag.type == 'X')
		put_len = print_hex(flag, ap);
	else
		put_len = 0;
	return (put_len);
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	t_flag		flag;
	int			i;
	int			put_len;

	va_start(ap, s);
	i = 0;
	put_len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			i += read_minus_and_zero(&s[i], &flag);
			i += read_width(&s[i], &flag, ap);
			i += read_precision(&s[i], &flag, ap);
			i += read_format_type(&s[i], &flag);
			put_len += print_format(flag, ap);
		}
		else
			put_len += write(STDOUT_FILENO, &s[i++], 1);
	}
	va_end(ap);
	return (put_len);
}
