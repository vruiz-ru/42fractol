#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

int     main(void)
{
	void    *win;
        void    *mlx;
        int win_width = 800;
	int win_height = 800;
        double a = 1; // Coeficiente de x^2
	double b = 0; // Coeficiente de x
	double c = 7;  // Constante
        int x_min = -20;
	int  x_max = 20;
        double x;
        double y;
        double scale_x;
        double scale_y;
        int screen_x;
        int screen_y;

        mlx = mlx_init();
        if (!mlx) 
	{
        	printf("Error: No se pudo inicializar MiniLibX.\n");
        	return (1);
	}
        win = mlx_new_window(mlx, win_width, win_height, "Curva eliptica");
        if (!win)
	{
        	printf("Error: No se pudo crear la ventana.\n");
        	return (1);
    	}
        scale_x = win_width / (x_max - x_min); // Escala horizontal
	scale_y = win_height / (x_max - x_min); // Escala vertical
        x = x_min;
        while (x <= x_max) 
	{
    		double discriminant = a * pow(x, 3) + b * x + c; // Verifica que el discriminante sea positivo
    			if (discriminant >= 0) 
			{
        			y = sqrt(discriminant); // Parte positiva
        			screen_x = (int)((x - x_min) * scale_x);
        			screen_y = (int)(win_height / 2 - y * scale_y);
        			if (screen_x >= 0 && screen_x < win_width && screen_y >= 0 && screen_y < win_height)
            			mlx_pixel_put(mlx, win, screen_x, screen_y, 0xff0000); // Dibuja en rojo

        			y = -sqrt(discriminant); // Parte negativa
        			screen_y = (int)(win_height / 2 - y * scale_y);
        			if (screen_x >= 0 && screen_x < win_width && screen_y >= 0 && screen_y < win_height)
            			mlx_pixel_put(mlx, win, screen_x, screen_y, 0xff0000); // Dibuja en rojo
			}
			x = x + 0.01;
	}
	mlx_loop(mlx);
	return (0);
}
