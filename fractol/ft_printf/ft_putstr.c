/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:27:46 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/07/30 21:04:11 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str != 0)
	{
		while (str[i] != '\0')
		{
			ft_putchar(str[i]);
			i++;
		}
		return (i);
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
}
