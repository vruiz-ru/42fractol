#ifndef PARABOLA_H
#define PARABOLA_H

#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#define ERROR_MESSAGE "Por favor introduce el formato correcto"

#define win_width	800
#define win_height	800


typedef struct s_mlx_data
{   
    //MLX
	void 	*mlx;
	void	*win;
    //HOOKS
    double shift_x;
    double shift_y;
    int mouse_x;
    int mouse_y;
	double x_min;
	double x_max;
    double zoom;
}				t_mlx_data;


#endif





