/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:54:29 by mkamei            #+#    #+#             */
/*   Updated: 2020/11/05 20:09:38 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_minus_and_zero(const char *s, t_flags *flags)
{
	int i;

	flags->minus = 0;
	flags->zero = 0;
	i = 0;
	while (s[i] == '-' || s[i] == '0')
	{
		if (s[i] == '-')
			flags->minus = 1;
		else
			flags->zero = 1;
		i++;
	}
	return (i);
}

static int	check_digit(const char *s, t_flags *flags, va_list ap, int f)
{
	int i;
	int num;

	i = 0;
	if (f == PRECISION && s[i++] != '.')
	{
		flags->precision = PRECISION_OFF;
		return (0);
	}
	num = 0;
	if (s[i] == '*')
	{
		num = va_arg(ap, int);
		i++;
	}
	else
		while (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + s[i++] - '0';
	if (f == WIDTH && num < 0)
		flags->minus = 1;
	if (f == WIDTH)
		flags->width = (int)ft_abs(num);
	else if (f == PRECISION)
		flags->precision = (num < 0) ? PRECISION_OFF : num;
	return (i);
}

static int	check_type(const char *s, t_flags *flags)
{
	int i;

	i = 0;
	flags->type = 'a';
	while (s[i] != '\0')
	{
		if (s[i] == 'c' || s[i] == 's' || s[i] == 'p' ||
			s[i] == 'd' || s[i] == 'i' || s[i] == 'u' ||
			s[i] == 'x' || s[i] == 'X' || s[i] == '%')
		{
			flags->type = s[i];
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

static int	printing(va_list ap, t_flags flags)
{
	int len;

	if (flags.type == 'c')
		len = print_c(ap, flags, PERCENT_OFF);
	else if (flags.type == '%')
		len = print_c(ap, flags, PERCENT_ON);
	else if (flags.type == 's')
		len = print_s(ap, flags);
	else if (flags.type == 'p' || flags.type == 'd' || flags.type == 'i' ||
			flags.type == 'u' || flags.type == 'x' || flags.type == 'X')
		len = print_pdiux(ap, flags);
	else
		len = 0;
	return (len);
}

int			ft_printf(const char *s, ...)
{
	va_list ap;
	t_flags flags;
	int		i;
	int		ret;

	va_start(ap, s);
	i = 0;
	ret = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			i += check_minus_and_zero(&s[i], &flags);
			i += check_digit(&s[i], &flags, ap, WIDTH);
			i += check_digit(&s[i], &flags, ap, PRECISION);
			i += check_type(&s[i], &flags);
			ret += printing(ap, flags);
		}
		else
			ret += write(1, &s[i++], 1);
	}
	va_end(ap);
	return (ret);
}
