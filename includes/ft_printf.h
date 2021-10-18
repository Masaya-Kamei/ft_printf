/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:53:21 by mkamei            #+#    #+#             */
/*   Updated: 2021/10/18 14:29:57 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define PRECISION_OFF -1

# include <stdarg.h>
# include <stdbool.h>
# include "libft.h"

typedef enum s_format_type
{
	CHAR			= 'c',
	STR				= 's',
	POINTER			= 'p',
	INT				= 'd',
	UINT			= 'u',
	SMALL_HEX		= 'x',
	LARGE_HEX		= 'X',
	PERCENT			= '%',
	NO_TYPE			= '\0'
}				t_format_type;

typedef enum s_nbr_symbol
{
	MINUS		= '-',
	HEX			= 'x',
	NO_SYMBOL	= '\0'
}			t_nbr_symbol;

typedef struct s_flag
{
	bool			minus;
	bool			zero;
	int				width;
	int				precision;
	t_format_type	type;
}					t_flag;

// main
int		ft_printf(const char *argv, ...);

// read_flag
int		read_minus_and_zero(const char *s, t_flag *flag);
int		read_width(const char *s, t_flag *flag, va_list ap);
int		read_precision(const char *s, t_flag *flag, va_list ap);
int		read_format_type(const char *s, t_flag *flag);

// print_flag
int		print_prefix_width_with_symbol(t_flag flag, int len, t_nbr_symbol symbol);
int		print_suffix_width(t_flag flag, int len, t_nbr_symbol symbol);
int		print_precision(t_flag flag, int len);

// print_format
int		print_char(const t_flag flag, va_list ap);
int		print_str(const t_flag flag, va_list ap);
int		print_pointer(const t_flag flag, va_list ap);
int		print_int(const t_flag flag, va_list ap);
int		print_uint(const t_flag flag, va_list ap);
int		print_hex(const t_flag flag, va_list ap);

// utils
int		putchar_for_size(const char c, const int size);
int		get_symbol_len(t_nbr_symbol symbol);
bool	is_nbr_format(t_format_type type);
bool	is_chars_format(t_format_type type);
int		count_ulong_digit_in_base(t_flag flag, unsigned long n, int base);
int		print_ulong_in_base(t_flag flag, unsigned long n, int base);

#endif
