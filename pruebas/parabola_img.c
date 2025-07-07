#include "parabola_img.h"

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

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*position;

	position = data->img.addr_pixels + ((y * data->img.line_length) + (x * (data->img.bits_per_pixel / 8)));
	*(unsigned int*)position = color;
}

void	print_parabola(t_mlx_data *data)
{
	
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
		y = data->a * pow(x, 2) + data->b * x + data->c;
		screen_x = ((int)((x - data->x_min) * scale_x) * data->zoom) + data->shift_x;
        screen_y = ((int)(win_height / 2 - y * scale_y) * data->zoom) + data->shift_y;
		if (screen_x >= 0 && screen_x < win_width && screen_y >= 0 && screen_y < win_height)
            my_mlx_pixel_put(data, screen_x, screen_y, 0xff0000); // Dibuja en rojo
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
	mlx_put_image_to_window(param->mlx,
							param->win,
							param->img.img_struct,
							0, 0);
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
	mlx_put_image_to_window(param->mlx,
							param->win,
							param->img.img_struct,
							0, 0);
	printf("The %d key has been pressed\n\n", button);
	return (0);
}

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
	events_init(data);
	// data_init(data);
}

void	image_init(t_mlx_data *data)
{
	//			void	*mlx_new_image(void *mlx_ptr,int width,int height);
	data->img.img_struct = mlx_new_image(data->mlx, win_width, win_height);
	if (NULL == data->img.img_struct)
	{
		mlx_destroy_image(data->mlx, data->img.img_struct);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	//char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
	data->img.addr_pixels = mlx_get_data_addr(data->img.img_struct, 
												&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

int	main(int ac, char *av[])
{	
	t_mlx_data data;

    if (ac < 4) 
    {
        printf("Se requieren al menos tres argumentos.\n");
        return (1);
    }
    data.a = strtod(av[1], NULL);//a = 1; // Coeficiente de x^2
    data.b = strtod(av[2], NULL);//1; // Coeficiente de x
    data.c = strtod(av[3], NULL);//1;  // Constante
    // Convertir los argumentos de cadena a double
    data.x_min = -5.0; //Convierte el primer argumento a double
    data.x_max = 5.0;
	data.shift_x = 0;
	data.shift_y = 0;
	data.zoom = 1;

	parabola_init(&data);
	image_init(&data);
	printf("Line_len %d <-> SIDE_LEN %d\n"
			"bpp %d\n"
			"endian %d\n", data.img.line_length, win_height, data.img.bits_per_pixel, data.img.endian);
	print_parabola(&data);
	//int		mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img_struct, 0, 0);
	mlx_loop(data.mlx);
	//int		mlx_destroy_image(void *mlx_ptr, void *img_ptr);
	mlx_destroy_image(data.mlx, data.img.img_struct);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
