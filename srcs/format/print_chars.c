/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:09:21 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 20:00:09 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf_develop.h"

static int	print_chars(const t_flag flag, const char *str, const int str_len)
{
	int		put_len;

	put_len = 0;
	put_len += print_prefix_width_with_symbol(flag, str_len, NO_SYMBOL);
	put_len += write(STDOUT_FILENO, str, str_len);
	put_len += print_suffix_width(flag, str_len, NO_SYMBOL);
	return (put_len);
}

int	print_char(const t_flag flag, va_list ap)
{
	char		c;
	const int	str_len = 1;

	if (flag.type == '%')
		c = '%';
	else
		c = va_arg(ap, int);
	return (print_chars(flag, &c, str_len));
}

int	print_str(const t_flag flag, va_list ap)
{
	char	*str;
	int		str_len;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	str_len = ft_strlen(str);
	if (flag.precision != PRECISION_OFF && str_len > flag.precision)
		str_len = flag.precision;
	return (print_chars(flag, str, str_len));
}
