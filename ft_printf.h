/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:53:21 by mkamei            #+#    #+#             */
/*   Updated: 2020/10/30 16:46:22 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define HEX_PREFIX 0
# define HEX_SMALL 1
# define HEX_LARGE 2

# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *argv, ...);

# endif
