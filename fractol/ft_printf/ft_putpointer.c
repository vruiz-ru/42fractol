/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:43:10 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/07/30 21:02:44 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recursive(unsigned long n, char *base)
{
	int	len;

	len = 0;
	if (n >= 16)
		len = len + ft_recursive(n / 16, base);
	len = len + ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putpointer(void *n, char *base)
{
	int	len;

	if (n != 0)
	{
		len = ft_putstr("0x");
		len = len + ft_recursive((unsigned long)n, base);
		return (len);
	}
	else
	{
		write (1, "(nil)", 5);
		return (5);
	}
}
