/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:53:21 by mkamei            #+#    #+#             */
/*   Updated: 2020/11/05 15:40:34 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define WIDTH 1
# define PRECISION 2
# define ALPHA_SIZE_SMALL 1
# define ALPHA_SIZE_LARGE 2
# define PERCENT_OFF 0
# define PERCENT_ON 1
# define ABS(x) ((x) < 0 ? -(x) : (x))

# include <stdarg.h>
# include "libft/libft.h"


#include <stdio.h>
typedef struct	s_flags
{
	int 		minus;
	int			zero;
	int 		width;
	int 		precision;
	char 		type;
}				t_flags;

int				ft_printf(const char *argv, ...);
int				putchar_num(char c, int num);
int 			print_c(va_list ap, t_flags flags, int percent);
int 			print_s(va_list ap, t_flags flags);
int 			print_pdiux(va_list ap, t_flags flags);


# endif
