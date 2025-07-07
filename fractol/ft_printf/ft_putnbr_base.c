/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:33:14 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/07/30 20:47:48 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(long n, char *base)
{
	int	lbase;
	int	len;

	len = 0;
	lbase = ft_strlen(base);
	if (n < 0)
	{
		n = -n;
		len = ft_putchar('-');
	}
	if (n >= lbase)
		len = len + ft_putnbr_base(n / lbase, base);
	len = len + ft_putchar(base[n % lbase]);
	return (len);
}
