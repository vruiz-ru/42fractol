/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:50:57 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/12/21 22:31:42 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pix + offset) = color;
}
// norminette 
/*
double	scale(double unscaled_num, double new_min, double new_max,
		double old_min, double old_max) {
	return (new_min + ((unescaled_num - old_min) * (new_max - new_min)
			/ (old_max - old_min));
}
*/

double	map(double unscaled_num, double new_min, double new_max,
		double old_max)
{
	return (new_min + (unscaled_num * (new_max - new_min) / (old_max)));
}

static void	init_pixel(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "mandelbrot", 10))
	{
		fractal->z.r = 0;
		fractal->z.i = 0;
		fractal->c.r = map(x, -2, +2, WIN_WIDTH) * fractal->zoom
			+ fractal->shift_x;
		fractal->c.i = map(y, +2, -2, WIN_HEIGHT) * fractal->zoom
			+ fractal->shift_y;
	}
	else
	{
		fractal->z.r = map(x, -2, +2, WIN_WIDTH) * fractal->zoom
			+ fractal->shift_x;
		fractal->z.i = map(y, +2, -2, WIN_HEIGHT) * fractal->zoom
			+ fractal->shift_y;
	}
}

static void	iterate_pixel(int x, int y, t_fractal *fractal)
{
	double	tmp;
	int		color;
	int		i;

	i = 0;
	while (i < fractal->iterations)
	{
		tmp = 2 * fractal->z.r * fractal->z.i + fractal->c.i;
		fractal->z.r = (fractal->z.r * fractal->z.r) - (fractal->z.i
				* fractal->z.i) + fractal->c.r;
		fractal->z.i = tmp;
		if (((fractal->z.r * fractal->z.r) + (fractal->z.i * fractal->z.i)) > 4)
		{
			color = map(i, BLACK, RED, fractal->iterations);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &fractal->img, NEON_FOREST);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			init_pixel(x, y, fractal);
			iterate_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img.img_ptr, 0,
		0);
}
