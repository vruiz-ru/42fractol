/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:50:57 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/12/21 22:37:53 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	memory_error(void)
{
	perror("Falló la reserva de memoria al iniciar X-server");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->iterations = 101;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	fractal->zoom = 1;
	fractal->z.r = 0;
	fractal->z.i = 0;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->win, KeyPress, KeyPressMask, handle_input, fractal);
	mlx_hook(fractal->win, ButtonPress, ButtonPressMask, handle_mouse, fractal);
	mlx_hook(fractal->win, DestroyNotify, StructureNotifyMask, handle_exit,
		fractal);
}

static void	fractal_init(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		memory_error();
	fractal->win = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT,
			fractal->name);
	if (!fractal->win)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		memory_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx, fractal->win);
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		memory_error();
	}
	fractal->img.pix = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

int	main(int ac, char *av[])
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)) || (ac == 4
			&& !ft_strncmp(av[1], "julia", 5)))
	{
		fractal.name = av[1];
		if (ac == 4 && !ft_strncmp(av[1], "julia", 5))
		{
			fractal.c.r = atodbl(av[2]);
			fractal.c.i = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx);
		return (0);
	}
	else
	{
		ft_printf("Introduce un formato válido:\n\t\"./a.out mandelbrot"
			"or \n\t\"./a.out julia <valor_real> <valor_imaginario>\"\n");
		return (EXIT_FAILURE);
	}
}
