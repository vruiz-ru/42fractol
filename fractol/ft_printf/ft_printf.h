/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:47:47 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/07/30 20:43:52 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H	
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar(char c);

int	ft_putstr(char *str);

int	ft_strlen(char *str);

int	ft_putnbr_base(long n, char *base);

int	ft_putpointer(void *n, char *base);

int	ft_printf(const char *format, ...);

#endif
