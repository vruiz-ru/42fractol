/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:50:57 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/12/21 22:56:23 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_exit(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx, fractal->win);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

int	handle_input(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += 0.5 * fractal->zoom;
	else if (keysym == XK_Right)
		fractal->shift_x -= 0.5 * fractal->zoom;
	else if (keysym == XK_Up)
		fractal->shift_y -= 0.5 * fractal->zoom;
	else if (keysym == XK_Down)
		fractal->shift_y += 0.5 * fractal->zoom;
	else if (keysym == XK_plus)
	{
		fractal->iterations += 10;
		ft_printf("%d\n", fractal->iterations);
	}
	else if (keysym == XK_minus)
	{
		if (fractal->iterations > 1)
		{
			fractal->iterations -= 10;
			ft_printf("%d\n", fractal->iterations);
		}
	}
	fractal_render(fractal);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button1)
	{
		if (!ft_strncmp(fractal->name, "julia", 5))
		{
			fractal->c.r = map(x, -2, +2, WIN_WIDTH) * fractal->zoom
				+ fractal->shift_x;
			fractal->c.i = map(y, +2, -2, WIN_WIDTH) * fractal->zoom
				+ fractal->shift_y;
			fractal_render(fractal);
		}
	}
	else if (button == Button5)
		fractal->zoom *= 1.05;
	else if (button == Button4)
		fractal->zoom *= 0.95;
	fractal_render(fractal);
	return (0);
}
