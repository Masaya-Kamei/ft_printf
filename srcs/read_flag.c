/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:19:02 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/16 18:16:31 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	read_minus_and_zero(const char *s, t_flag *flag)
{
	int		i;

	flag->minus = 0;
	flag->zero = 0;
	i = 0;
	while (s[i] == '-' || s[i] == '0')
	{
		if (s[i] == '-')
			flag->minus = 1;
		else
			flag->zero = 1;
		i++;
	}
	return (i);
}

static int	read_num(const char *s, va_list ap, int *num)
{
	int		i;

	i = 0;
	if (s[i] == '*')
	{
		*num = va_arg(ap, int);
		i++;
	}
	else
	{
		*num = 0;
		while (s[i] >= '0' && s[i] <= '9')
			*num = *num * 10 + s[i++] - '0';
	}
	return (i);
}

int	read_width(const char *s, t_flag *flag, va_list ap)
{
	int		i;

	i = read_num(s, ap, &flag->width);
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width *= -1;
	}
	return (i);
}

int	read_precision(const char *s, t_flag *flag, va_list ap)
{
	int		i;

	i = 0;
	if (s[i++] != '.')
	{
		flag->precision = PRECISION_OFF;
		return (0);
	}
	i += read_num(&s[i], ap, &flag->precision);
	if (flag->precision < 0)
		flag->precision = PRECISION_OFF;
	return (i);
}

int	read_type(const char *s, t_flag *flag)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'c' || s[i] == 's' || s[i] == 'p'
			|| s[i] == 'd' || s[i] == 'i' || s[i] == 'u'
			|| s[i] == 'x' || s[i] == 'X' || s[i] == '%')
		{
			flag->type = s[i];
			i++;
			return (i);
		}
		i++;
	}
	flag->type = NO_TYPE;
	return (i);
}
