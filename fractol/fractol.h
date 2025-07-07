/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:50:33 by vruiz-ru          #+#    #+#             */
/*   Updated: 2024/12/21 22:53:25 by vruiz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 650
# define WIN_HEIGHT 650

// COLORS
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define EMERALD_VIBE 0x00FF80
# define CELESTIAL_BLUE 0x33CCFF
# define LUMINOUS_GREEN 0x66FF00
# define OCEAN_BLISS 0x00CC66
# define MYSTIC_AQUA 0x3399CC
# define NEON_FOREST 0x66FF66
# define TEAL_GLOW 0x00CCCC

typedef struct s_atodbl
{
	long		integer_part;
	double		fractional_part;
	double		pow;
	int			sign;
	int			has_decimal;
	int			has_digit;
	double		sol;
}				t_atodbl;

typedef struct s_image
{
	void		*img_ptr;
	char		*pix;
	int			bpp;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_complex
{
	double		r;
	double		i;
}				t_complex;

typedef struct s_fractal
{
	char		*name;
	void		*mlx;
	void		*win;
	t_image		img;
	int			iterations;
	double		shift_x;
	double		shift_y;
	double		zoom;
	t_complex	z;
	t_complex	c;
}				t_fractal;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			fractal_render(t_fractal *fractal);
double			map(double unscaled_num, double new_min, double new_max,
					double old_max);
int				handle_input(int keysym, t_fractal *fractal);
int				handle_exit(t_fractal *fractal);
int				handle_mouse(int button, int x, int y, t_fractal *fractal);
double			atodbl(char *s);

#endif
