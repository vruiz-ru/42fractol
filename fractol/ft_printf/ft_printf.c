/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:33:52 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/07/30 20:45:05 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_condition(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 's')
		len = ft_putstr (va_arg(args, char *));
	else if (c == 'c')
		len = ft_putchar((char)va_arg(args, int));
	else if (c == 'd' || c == 'i')
		len = ft_putnbr_base(va_arg(args, int), "0123456789");
	else if (c == 'u')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789");
	else if (c == 'X')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == 'x')
		len = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'p')
		len = ft_putpointer(va_arg(args, void *), "0123456789abcdef");
	else if (c == '%')
		len = ft_putchar ('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			len = len + ft_condition(format[i], args);
			i++;
		}
		else
		{
			len = len + ft_putchar(format[i]);
			i++;
		}
	}
	va_end (args);
	return (len);
}
