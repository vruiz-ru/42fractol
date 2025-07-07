# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vruiz-ru <vruiz-ru@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/14 19:29:09 by vruiz-ru          #+#    #+#              #
#    Updated: 2024/12/21 22:49:11 by vruiz-ru         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol
SRCS	= events.c \
		fractol.c \
		ft_strncmp.c \
		julia.c \
		render.c \

CC = gcc
OBJS = $(SRCS:.c=.o)
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror 
MLX = minilibx-linux/libmlx.a
PRINTF = ft_printf/libftprintf.a
FT_PRINTF_DIR = ./ft_printf
LFLAGS =  -Ift_printf -Lft_printf -Iminilibx-linux -Lminilibx-linux -lXext -lX11 -lm -lz
CLEAN = clean

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ -I.

all: $(NAME)

$(MLX):
			$(MAKE) -C ./minilibx-linux
		
$(PRINTF):
			$(MAKE) -C $(FT_PRINTF_DIR)	

$(NAME): $(PRINTF) $(MLX) $(OBJS) 
	 $(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(MLX) -o $(NAME) $(LFLAGS)

fclean: clean 
	$(RM) $(NAME)
	$(RM) $(PRINTF)
	
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	
re: fclean all

.PHONY: all clean fclean re .c.o