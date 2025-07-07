#include "parabola.h"

int	close_window(t_mlx_data *param) 
{
    (void)param; // Si no usas el parámetro, evita el warning.
    printf("Cerrando la ventana...\n");
	mlx_destroy_window(param->mlx, param->win);
	//mlx_destroy_window(mlx, win2);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
    exit(1); // Finaliza el programa.
	return(0);
}

void	print_parabola(t_mlx_data *data)
{
	double a = 1; // Coeficiente de x^2
    double b = 1; // Coeficiente de x
    double c = 1;  // Constante
	double x;
	double y;
	double scale_x;
	double scale_y;
	int screen_x;
	int screen_y;

	 
	scale_x = win_width / (data->x_max - data->x_min); // Escala horizontal
    scale_y = win_height / (data->x_max - data->x_min); // Escala vertical
	x = data->x_min;
	while (x <= data->x_max)
	{	
		y = a * pow(x, 2) + b * x + c;
		screen_x = ((int)((x - data->x_min) * scale_x) * data->zoom) + data->shift_x;
        screen_y = ((int)(win_height / 2 - y * scale_y) * data->zoom) + data->shift_y;
		if (screen_x >= 0 && screen_x < win_width && screen_y >= 0 && screen_y < win_height)
            mlx_pixel_put(data->mlx, data->win, screen_x, screen_y, 0xff0000); // Dibuja en rojo
		x = x + 0.01;
	}
}

int	handle_input(int keysym, t_mlx_data *param)
{
	if (keysym == XK_Escape)
	{
		printf("The %dd key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(param->mlx, param->win);
		//mlx_destroy_window(mlx, win2);
		mlx_destroy_display(param->mlx);
		free(param->mlx);
		exit(1);
	}
	else if (keysym == XK_Left)
		param->shift_x -= 50;
	else if (keysym == XK_Right)
		param->shift_x += 50;
	else if (keysym == XK_Up)
		param->shift_y -= 50;
	else if (keysym == XK_Down)
		param->shift_y += 50;
	else if (keysym == XK_plus)
		param->zoom *= 1.1;
	else if (keysym == XK_minus)
		param->zoom *= 0.9;
	mlx_clear_window(param->mlx, param->win);
	print_parabola(param);
	printf("The %d key has been pressed\n\n", keysym);
	
	return(0);
}

int handle_mouse(int button, int x, int y, t_mlx_data *param)
{
    if (button == Button1) // Botón izquierdo
        printf("Left click at (%d, %d)\n", x, y);
    else if (button == Button3) // Botón derecho
        printf("Right click at (%d, %d)\n", x, y);
	else if (button == Button4)
	{	
		printf("Zoom in at (%d, %d)\n", x, y);
		param->zoom *= 1.1;
	}
	else if (button == Button5)
	{	
		printf("Zoom out at (%d, %d)\n", x, y);
		param->zoom *= 0.9;
	}
    else
        printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);

	mlx_clear_window(param->mlx, param->win);
	print_parabola(param);
	printf("The %d key has been pressed\n\n", button);
	return (0);
}


/*int	zoom(int button, int x, int y, t_mlx_data *param)
{
    if (button == 4) // Rueda del ratón hacia arriba (zoom in)
    {
        param->zoom_factor += 2;
		printf("parazoom -->> %d\n", param->zoom_factor);
    }
    else if (button == 5) // Rueda del ratón hacia abajo (zoom out)
	{
    	if (param->zoom_factor > 2) {
        	param->zoom_factor -= 2;  // Reduce el zoom en 2
    	} else {
        	param->zoom_factor = 2;  // Establece el zoom a 2 si es menor o igual a 2
    	}
	}
	// Guardar las coordenadas del ratón
    param->mouse_x = x;
    param->mouse_y = y;

	// Convertir coordenadas del ratón de píxeles a coordenadas matemáticas
    double range_x = param->x_max - param->x_min; // Rango actual en X
    double center_x = param->x_min + ((double)x / win_width) * range_x;

    // Ajustar el rango de X para centrar en el ratón y aplicar el zoom
    double new_range_x = range_x / param->zoom_factor; // Nuevo rango en X
    param->x_min = center_x - new_range_x / 2.0;
    param->x_max = center_x + new_range_x / 2.0;

    printf("Zoom: %d, Mouse Position: (%d, %d)\n", param->zoom_factor, param->mouse_x, param->mouse_y);
    
    // Limpiar la ventana antes de redibujar
    mlx_clear_window(param->mlx, param->win);
    
    print_parabola (param);
    // Para este ejemplo, solo mostramos el nivel de zoom y la posición del ratón.
    mlx_string_put(param->mlx, param->win, param->mouse_x, param->mouse_y, 0xFFFFFF, "Zoom!");

    return (0);
}*/

void	events_init(t_mlx_data *data)
{
	//int mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
	mlx_key_hook(data->win, handle_input, data);
	//void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, handle_mouse, data); 
	//int		mlx_mouse_hook(void *win_ptr, int (*f)(), void *param);
	//mlx_mouse_hook(data->win, zoom,  data);
}

void	parabola_init(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx) 
	{
        printf("Error: No se pudo inicializar MiniLibX.\n");
		exit(EXIT_FAILURE);
    }
	data->win = mlx_new_window(data->mlx, win_width, win_height, "Parabolic try");
	if (!data->win) 
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
        printf("Error: No se pudo crear la ventana.\n");
		exit(EXIT_FAILURE);
    }
	/* Doble ventana
	win2 = mlx_new_window(mlx, win_width, win_height, "2nd")
	if (!win) 
	{
		mlx_destroy_display(mlx);
		free(mlx);
        printf("Error: No se pudo crear la ventana.\n");
        return (1);
    }
	*/
	events_init(data);
	// data_init(data);

}

int	main(void)
{	
	t_mlx_data data;
	
    data.x_min = -5.0;     // Límite inferior de la parábola en X
    data.x_max = 5.0;
	data.shift_x = 0;
	data.shift_y = 0;
	data.zoom = 1;
	parabola_init(&data);
	
	print_parabola(&data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	//mlx_destroy_window(mlx, win2);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
