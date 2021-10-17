/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:53:21 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/17 11:16:51 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define ALPHA_SIZE_SMALL 1
# define ALPHA_SIZE_LARGE 2
# define PERCENT_OFF 0
# define PERCENT_ON 1
# define PRECISION_OFF -1
# define PUT_ZERO_SO_SKIP -1

# include <stdarg.h>
# include <stdbool.h>
# include "libft.h"

typedef enum s_format_type
{
	CHAR			= 'c',
	STR				= 's',
	POINTER			= 'p',
	INT				= 'd',
	UNSIGNED_INT	= 'u',
	SMALL_HEX		= 'x',
	LARGE_HEX		= 'X',
	PERCENT			= '%',
	NO_TYPE			= '\0'
}				t_format_type;

typedef struct s_flag
{
	bool			minus;
	bool			zero;
	int				width;
	int				precision;
	t_format_type	type;
}					t_flag;

int		ft_printf(const char *argv, ...);

// read_flag
int		read_minus_and_zero(const char *s, t_flag *flag);
int		read_width(const char *s, t_flag *flag, va_list ap);
int		read_precision(const char *s, t_flag *flag, va_list ap);
int		read_type(const char *s, t_flag *flag);

// print_format
int		print_char(const t_flag flag, va_list ap, bool is_percent);
int		print_str(const t_flag flag, va_list ap);
int		print_pointer(const t_flag flag, va_list ap);
int		print_int(const t_flag flag, va_list ap);
int		print_unsigned_int(const t_flag flag, va_list ap);
int		print_hex(const t_flag flag, va_list ap, bool is_large_alpha);
// int		print_pdiux(const t_flag flag, va_list ap);

// utils
int		putchar_for_size(const char c, const int size);
int		count_ulong_digit_in_base(unsigned long n, int base);
int		put_ulong_in_base(unsigned long n, int base, bool is_large_alpha);

#endif
