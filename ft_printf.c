/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:54:29 by mkamei            #+#    #+#             */
/*   Updated: 2020/10/29 18:47:19 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


#include <stdio.h>


void		ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	if (n >= 10)
		ft_putnbr_unsigned_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void		ft_puthex_fd(long n, int fd, int flag)
{
	if (n >= 16)
		ft_puthex_fd(n / 16, fd, flag);
	else
	{
		if (flag == HEX_PREFIX)
			ft_putstr_fd("0x", fd);
	}
	if (n % 16 >= 10)
	{
		if (flag == HEX_LARGE)
			ft_putchar_fd(n % 16 + '0' + 7, fd);
		else
			ft_putchar_fd(n % 16 + '0' + 39, fd);
	}
	else
		ft_putchar_fd(n % 16 + '0', fd);
}


int		ft_printf(const char *s, ...)
{
	va_list list;
	int		i;

	va_start(list, s);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'c')
				ft_putchar_fd(va_arg(list, int), 1);
			else if (s[i] == 's')
				ft_putstr_fd(va_arg(list, char *), 1);
			else if (s[i] == 'p')
				ft_puthex_fd((long)va_arg(list, void *), 1, HEX_PREFIX);
			else if (s[i] == 'd' || s[i] == 'i')
				ft_putnbr_fd(va_arg(list, int), 1);
			else if (s[i] == 'u')
				ft_putnbr_unsigned_fd(va_arg(list, int), 1);
			else if (s[i] == 'x')
				ft_puthex_fd(va_arg(list, int), 1, HEX_SMALL);
			else if (s[i] == 'X')
				ft_puthex_fd(va_arg(list, int), 1, HEX_LARGE);
			else if (s[i] == '%')
				ft_putchar_fd('%', 1);
		}
		else
			ft_putchar_fd(s[i], 1);
		i++;
	}

	va_end(list);
	return (0);
}
