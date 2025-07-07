/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:50:57 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/12/21 20:03:48 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static void	error_message(void)
{
	ft_printf("Introduce un numero real válido entre -2 y 2\n");
	exit(EXIT_FAILURE);
}

static void	atodbl_init(t_atodbl *doble)
{
	doble->integer_part = 0;
	doble->fractional_part = 0;
	doble->sign = +1;
	doble->pow = 1;
	doble->has_decimal = 0;
	doble->has_digit = 0;
}

static void	loop(char *s, t_atodbl *doble)
{
	while (*s)
	{
		if (*s == '.')
		{
			if (doble->has_decimal)
				error_message();
			doble->has_decimal = 1;
		}
		else if (ft_isdigit(*s))
		{
			doble->has_digit = 1;
			if (!doble->has_decimal)
				doble->integer_part = (doble->integer_part * 10) + (*s - '0');
			else
			{
				doble->pow /= 10;
				doble->fractional_part = doble->fractional_part + (*s - '0')
					* doble->pow;
			}
		}
		else
			error_message();
		++s;
	}
}

double	atodbl(char *s)
{
	t_atodbl	doble;

	atodbl_init(&doble);
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		++s;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			doble.sign = -doble.sign;
	loop(s, &doble);
	doble.sol = (doble.integer_part + doble.fractional_part) * doble.sign;
	if (!doble.has_digit)
		error_message();
	else if (doble.sol < -2 || doble.sol > 2)
		error_message();
	return (doble.sol);
}
